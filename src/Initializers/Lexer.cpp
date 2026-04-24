#include "Configs/LexerConfigs.hpp"

vector<Token<string>> Lexer::Tokenize() {
    vector<Token<string>> Tokens;
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
            Tokens.push_back(Token<string>(END_OF_FILE));
            break;
        }
        else if (regex_match(CurrentWord, Keywords)) Tokens.push_back(HandleKeywords(CurrentWord));
        else if (regex_match(CurrentWord, Special)) Tokens.push_back(HandleSpecial(CurrentWord));
        else if (regex_match(CurrentWord, Variables) || PreviousIsVarDef()) Tokens.push_back(HandleVariables(CurrentWord));
        else if (regex_match(CurrentWord, Comparison) || IsCompEqual()) Tokens.push_back(HandleComparison(CurrentWord));
        else if (regex_match(CurrentWord, Assignment)) Tokens.push_back(HandleAssignment(CurrentWord));
        else if (regex_match(CurrentWord, Arithmetic)) Tokens.push_back(HandleArithmetic(CurrentWord));
        else if (regex_match(CurrentWord, Logic)) Tokens.push_back(HandleLogic(CurrentWord));
        else if (regex_match(CurrentWord, Others)) Tokens.push_back(HandleOthers(CurrentWord));
        else if (regex_match(CurrentWord, Grouping)) Tokens.push_back(HandleGrouping(CurrentWord));
        else Tokens.push_back(HandleDataTypes(CurrentWord));
        
        if (Position >= Source.data() + Source.size()) {
            Tokens.push_back(Token<string>(END_OF_FILE));
            break;
        }
    }
    
    return Tokens;
}