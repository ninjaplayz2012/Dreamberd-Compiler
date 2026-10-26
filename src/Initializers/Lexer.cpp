#include "Headers/Lexer.hpp"

vector<Token<string>> Lexer::Tokenize() {
    vector<Token<string>> Tokens;
    vector<string> Idents;
    vector<string> Globals;
    Token<string> PreviousToken;
    string CurrentWord;
    bool Continue = true;
    
    regex Special(R"(\!|\?|¡)");
    regex Variables(R"(var|const|g_.*\S)");
    regex Comparison(R"([><;]{1}=|[<>])");
    regex Assignment(R"([\+\-\*/%]{0,1}=)");
    regex Arithmetic(R"(/\+\+|--|[+\-*\/%])");
    regex Logic(R"(&&|\|\||;)");
    regex Keywords(R"(if|elseif|else|when|return|fu?n?c?t?i?o?n?|previous|await|next|class|async)");
    regex Others(R"(\.|:|,)");
    regex Grouping(R"([{}()])");
    
    auto PreviousIsVarDef = [&PreviousToken]{ return PreviousToken.Id == CONST || PreviousToken.Id == VAR; };
    auto IsCompEqual = [&PreviousToken, &CurrentWord](){ return !(PreviousToken.Id == IDENT || PreviousToken.Id == GLOBAL) && regex_match(CurrentWord, (regex)R"(={1,4})"); };
    
    while (Continue) {
        CurrentWord = GetNextWord();
        if (Tokens.size() > 0) PreviousToken = Tokens.back();
        
        std::cout << CurrentWord << "\n";
        
        if (CurrentWord.empty()) {
            Tokens.push_back(Token<string>(END_OF_FILE, "", "", CurrentLine));
            break;
        }
        else if (regex_match(CurrentWord, Keywords)) {
            auto Token = HandleKeywords(CurrentWord);
            Token.Line = CurrentLine;
            Tokens.push_back(Token);
        }
        else if (regex_match(CurrentWord, Special)) {
            auto Token = HandleSpecial(CurrentWord);
            Token.Line = CurrentLine;
            if (Token.Id == END_LINE || Token.Id == END_LINE_2) CurrentLine++;
            Tokens.push_back(Token);
        }
        else if (regex_match(CurrentWord, Variables) || PreviousIsVarDef()) {
            auto Token = HandleVariables(CurrentWord);
            Token.Line = CurrentLine;
            Tokens.push_back(Token);
            if (Token.Id == IDENT && std::find(Idents.begin(), Idents.end(), Token.Name) == Idents.end()) Idents.push_back(Token.Name);
            if (Token.Id == GLOBAL && std::find(Globals.begin(), Globals.end(), Token.Name) == Globals.end()) Globals.push_back(Token.Name);
        }
        else if (std::find(Idents.begin(), Idents.end(), CurrentWord) != Idents.end()) Tokens.emplace_back(IDENT, CurrentWord, CurrentWord, CurrentLine);
        else if (std::find(Globals.begin(), Globals.end(), CurrentWord) != Globals.end()) Tokens.emplace_back(IDENT, CurrentWord, CurrentWord, CurrentLine);
        else if (regex_match(CurrentWord, Comparison) || IsCompEqual()) {
            auto Token = HandleComparison(CurrentWord);
            Token.Line = CurrentLine;
            Tokens.push_back(Token);
        }
        else if (regex_match(CurrentWord, Assignment)) {
            auto Token = HandleAssignment(CurrentWord);
            Token.Line = CurrentLine;
            Tokens.push_back(Token);
        }
        else if (regex_match(CurrentWord, Arithmetic)) {
            auto Token = HandleArithmetic(CurrentWord);
            Token.Line = CurrentLine;
            Tokens.push_back(Token);
        }
        else if (regex_match(CurrentWord, Logic)) {
            auto Token = HandleLogic(CurrentWord);
            Token.Line = CurrentLine;
            Tokens.push_back(Token);
        }
        else if (regex_match(CurrentWord, Others)) {
            auto Token = HandleOthers(CurrentWord);
            Token.Line = CurrentLine;
            Tokens.push_back(Token);
        }
        else if (regex_match(CurrentWord, Grouping)) {
            auto Token = HandleGrouping(CurrentWord);
            Token.Line = CurrentLine;
            Tokens.push_back(Token);
        }
        else {
            auto Token = HandleDataTypes(CurrentWord);
            Token.Line = CurrentLine;
            Tokens.push_back(Token);
        }
        
        if (Position >= Source.data() + Source.size()) {
            Tokens.push_back(Token<string>(END_OF_FILE, "", "", CurrentLine));
            break;
        }
    }
    
    return Tokens;
}