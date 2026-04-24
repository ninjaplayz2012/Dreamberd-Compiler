#pragma once

#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <array>
#include <regex>
#include <cctype>
#include <variant>
#include <unordered_set>
#include "Headers/Tokens.h"

/*--{ Functions }--*/
using 
std::isspace,
std::isdigit,
std::regex_match,
std::string, 
std::vector, 
std::array, 
std::regex,
std::unordered_set,
std::variant;

/*--{ Structs }--*/
template <typename ValueType>
struct Token {
	Tokens Id = UNKNOWN;
	ValueType Value;
	string Name;
	
	Token(Tokens Id, ValueType Value, string Name) : Id(Id), Value(Value), Name(Name) {}
	Token(Tokens Id, ValueType Value) : Id(Id), Value(Value) {}
	Token(Tokens Id) : Id(Id) {}
	Token() = default;
	
	friend std::ostream& operator<<(std::ostream &os, const Token<ValueType>& token) {
		os << "------------------------------------\n"
		<< "Token Data\n"
		<< "Id: " << TokenToString(token.Id) << "\n"
		<< "Value: " << token.Value << "\n"
		<< "Name: " << token.Name << "\n"
		<< "------------------------------------\n";
		return os; 
	}
};

/*--{ Classes }--*/
class Lexer {
	public:
		Lexer(string &Source) : Source(Source) {}
		
		vector<Token<string>> Tokenize();
	private:
		string Source;
		const char *Position = Source.data();
		char CurrentChar = Source[0];
		
		const string Delimiters = ".()!?¡;,+-*/=<>:\"'";
		const string UnskippableDelimeters = ",:.!?¡()";
		
		char Advance() {
			if (*Position == '\0') return '\0';
			
			Position += 1;
			CurrentChar = *Position;
			return CurrentChar;
		};
		
		char Peek(int Offset) {
			return *(Position + Offset);
		};
		
		void UpdateState(const char* NewPos) {
			Position = NewPos;
			CurrentChar = *NewPos;
		}
		
		void SkipWhitespace() {
			while (CurrentChar != '\0' && isspace(CurrentChar)) {
				Advance();
			}
		};
		
		string GetNextWord() {
			SkipWhitespace();
			string Result = "";
			
			auto HandleQuotedString = [&](char Quote) {
				int QuoteCount = 0;
				const char* Start = Position;
				
				// Count opening quotes
				while (*Position == Quote) {
					QuoteCount++;
					Position++;
				}
				
				// Find matching closing sequence
				const char* Search = Position;
				while (*Search != '\0') {
					if (*Search == Quote) {
						// Count closing quotes at this position
						int Closing = 0;
						const char* CloseStart = Search;
						while (*Search == Quote) {
							Closing++;
							Search++;
						}
						if (Closing == QuoteCount) {
							Result.append(Start, Search - Start);
							UpdateState(Search);
							return;
						}
					} else {
						Search++;
					}
				}
			};

			if (CurrentChar == '\'') { HandleQuotedString('\''); return Result; }
			if (CurrentChar == '"')  { HandleQuotedString('"');  return Result; }
			
			auto CurrentCharGood = [&](){return CurrentChar != '\0' && !isspace(CurrentChar) && Delimiters.find(CurrentChar) == string::npos;};
			auto NextCharGood = [&]() {
				if (isspace(CurrentChar) || CurrentChar == '\0') return false;
				char next = *(Position + 1);
				bool isNotSpace = !isspace(next);
				bool isStandardDelim = UnskippableDelimeters.find(CurrentChar) == string::npos;

				if (CurrentChar == '.') return isNotSpace && isdigit(next);
				return isNotSpace && isStandardDelim;
			};
			
			// Comment this later
			if (Delimiters.find(CurrentChar) != string::npos && !NextCharGood()) {
				Result += CurrentChar;
				Advance();
				
				return Result;
			}
			
			while (CurrentCharGood() || NextCharGood()) {
				Result += CurrentChar;
				Advance();
			}
			
			if (CurrentChar != '\0' && !isspace(CurrentChar) &&
				Delimiters.find(CurrentChar) != string::npos &&
				UnskippableDelimeters.find(CurrentChar) == string::npos) {
				Result += CurrentChar;
				Advance();
			}
			
			return Result;
		};
		
		// Like handling
		Token<string> HandleSpecial(string Data) {
			const regex ENDLINE_r("!");
			const regex DEBUG_r(R"(\?)");
			const regex ENDLINE2_r("¡");
			
			if (regex_match(Data, ENDLINE_r)) return Token<string>(END_LINE, Data, Data);
			else if (regex_match(Data, ENDLINE2_r)) return Token<string>(END_LINE_2, Data, Data);
			else if (regex_match(Data, DEBUG_r)) return Token<string>(DEBUG, Data, Data);
			else if (Position == (Source.data() + Source.size())) return Token<string>(END_OF_FILE);
			else return Token(UNKNOWN, Data, Data);
		};
		
		Token<string> HandleDataTypes(string Data) {
			
			// Use else to return a string because strings can have 0 quotes
			const regex STRING_r(R"('.+')");
			const regex STRING2_r(R"(".+")");
			const regex FLOAT_r(R"(\d*\.\d+)");
			const regex FRACTION_r(R"(\d+/\d+)");
			const regex INT_r(R"(\d+)");
			const regex BOOL_r(R"([tT]rue|[fF]alse|[mM]aybe)");
			
			if (regex_match(Data, STRING_r)) {
				string ChangedData = Data;
				std::erase(ChangedData, '\'');
				return Token(STRING, ChangedData, Data);
			} else if (regex_match(Data, STRING2_r)) {
				string ChangedData = Data;
				std::erase(ChangedData, '\"');
				return Token(STRING, ChangedData, Data);
			} else if (regex_match(Data, BOOL_r)) {
				string ChangedData = Data;
				std::transform(ChangedData.begin(), ChangedData.end(), ChangedData.begin(), [](unsigned char c){ return std::tolower(c); });
				return Token(BOOL, ChangedData, Data);
			} else if (regex_match(Data, FLOAT_r)) return Token(FLOAT, Data, Data);
			else if (regex_match(Data, FRACTION_r)) return Token(FRACTION, Data, Data);
			else if (regex_match(Data, INT_r)) return Token(INT, Data, Data);
			else return Token(STRING, Data, Data);
		};
		
		Token<string> HandleVariables(string Data) {
			regex GLOBAL_r(R"(g_.*\S)");
			
			if (Data == "var") return Token(VAR, Data, Data);
			else if (Data == "const") return Token(CONST, Data, Data);
			else if (regex_match(Data, GLOBAL_r)) return Token(GLOBAL, Data, Data);
			else return Token(IDENT, Data, Data);
		};
		
		Token<string> HandleAssignment(string Data) {
			if (Data == "=") return Token(EQUALS_A, Data, Data);
			else if (Data == "+=") return Token(EQUALS_ADD_A, Data, Data);
			else if (Data == "-=") return Token(EQUALS_SUB_A, Data, Data);
			else if (Data == "*=") return Token(EQUALS_MUL_A, Data, Data);
			else if (Data == "/=") return Token(EQUALS_DIV_A, Data, Data);
			else if (Data == "%=") return Token(EQUALS_MOD_A, Data, Data);
			else return Token(UNKNOWN, Data, Data);
		};
		
		Token<string> HandleArithmetic(string Data) {
			if (Data == "+") return Token(ADD, Data, Data);
			else if (Data == "-") return Token(SUB, Data, Data);
			else if (Data == "*") return Token(MUL, Data, Data);
			else if (Data == "/") return Token(DIV, Data, Data);
			else if (Data == "%") return Token(MOD, Data, Data);
			else if (Data == "++") return Token(INC, Data, Data);
			else if (Data == "--") return Token(DEC, Data, Data);
			else return Token(UNKNOWN, Data, Data);
		};
		
		Token<string> HandleComparison(string Data) {
			if (regex_match(Data, (regex)"={1,4}")) return Token(EQUALS, Data, Data);
			else if (Data == ";=") return Token(NOT_EQUAL, Data, Data);
			else if (Data == ">=") return Token(GREATER_EQ, Data, Data);
			else if (Data == "<=") return Token(LESS_EQ, Data, Data);
			else if (Data == ">") return Token(GREATER, Data, Data);
			else if (Data == "<") return Token(LESS, Data, Data);
			else return Token(UNKNOWN, Data, Data);
		};
		
		Token<string> HandleLogic(string Data) {
			if (Data == "&&") return Token(AND, Data, Data);
			else if (Data == "||") return Token(OR, Data, Data);
			else if (Data == ";") return Token(NOT, Data, Data);
			else return Token(UNKNOWN, Data, Data);
		};
		
		Token<string> HandleKeywords(string Data) {
			if (Data == "if") return Token(IF, Data, Data);
			else if (Data == "elseif") return Token(ELSE_IF, Data, Data);
			else if (Data == "else") return Token(ELSE, Data, Data);
			else if (Data == "when") return Token(WHEN, Data, Data);
			else if (Data == "return") return Token(RETURN, Data, Data);
			else if (regex_match(Data, (regex)R"((?=.)f?u?n?c?t?i?o?n?)")) return Token(FUNCTION, Data, Data);
			else if (Data == "previous") return Token(PREVIOUS, Data, Data);
			else if (Data == "await") return Token(AWAIT, Data, Data);
			else if (Data == "next") return Token(NEXT, Data, Data);
			else if (Data == "class") return Token(CLASS, Data, Data);
			else if (Data == "async") return Token(ASYNC, Data, Data);
			else return Token(UNKNOWN, Data, Data);
		};
		
		Token<string> HandleOthers(string Data) {
			if (Data == ",") return Token(COMMA, Data, Data);
			else if (Data == ".") return Token(DOT, Data, Data);
			else if (Data == ":") return Token(COLON, Data, Data);
			else return Token(UNKNOWN, Data, Data);
		};
		
		Token<string> HandleGrouping(string Data) {
			if (Data == "(") return Token(LPAREN, Data, Data);
			else if (Data == ")") return Token(RPAREN, Data, Data);
			else if (Data == "{") return Token(LBRACE, Data, Data);
			else if (Data == "}") return Token(RBRACE, Data, Data);
			// else if (Data == ":") return Token(COLON, Data, Data);
			// else if (Data == ".") return Token(DOT, Data, Data);
			else return Token(UNKNOWN, Data, Data);
		}
};
