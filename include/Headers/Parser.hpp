#include "Configs/ParserConfigs.hpp"

#ifndef PARSER_CLASS_HPP
#define PARSER_CLASS_HPP

/*--{ AST Node Base Struct }--*/
struct ASTNode {
	virtual ~ASTNode() = default;
	
	virtual string ToString() {
		
	}
};

/*--{ AST Node Child Structs }--*/
struct VariableNode : virtual public ASTNode {
	string Identity;
	VariableValue Value;
	TOKENS DataType;
};

/*--{ Parser Class }--*/
class Parser {
	public:
		explicit Parser(vector<Token<string>> Tokens);
		
		vector<unique_ptr<ASTNode>> Parse();
		
	private:
		vector<Token<string>> Tokens;
		size_t Position = 0;
		Token<string> CurrentToken = Tokens[0];
		
		Token<string> Peek() const {
			return Tokens[Position + 1];
		}
		
		Token<string> Advance() {
			if (Position + 1 >= Tokens.size()) {
				CurrentToken = Tokens.back();
				return CurrentToken;
			}
			
			CurrentToken = Tokens[++Position];
			return CurrentToken;
		}
		
		Token<string> Consume(TOKENS ExpectedType, string ErrorMessage) {
			if (CurrentToken.Id == ExpectedType) return Advance();
			throw std::runtime_error(ErrorMessage + ": " + std::to_string(CurrentToken.Line));
		}
		
		bool CheckToken(TOKENS TokenType) const {
			return CurrentToken.Id == TokenType;
		}
		
		unique_ptr<ASTNode> ParseStatement();
		unique_ptr<ASTNode> ParseExpression();
		
		unique_ptr<VariableNode> ParseVariable() {
			
		}
};

#endif