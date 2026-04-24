// Long ahh tokens list, using hexadecimal to look cool
enum Tokens {
    // Special Tokens
    UNKNOWN     = -0x01, // IDFK
    END_OF_FILE =  0x00, // [INSERT END OF FILE]
    END_LINE    =  0x01, // !
    DEBUG       =  0x02, // ?
    END_LINE_2  =  0x03, // ¡
    
    // Datatype Tokens
    STRING   = 0x04, // "String"
    INT      = 0x05, // 10
    FLOAT    = 0x06, // 10.5
    FRACTION = 0x07, // 1/2 (1 / 2 is division)
    BOOL     = 0x08, // true
    NIL      = 0x09, // nil

    // Variable Tokens
    IDENT  = 0x0A, // VarName
    VAR    = 0x0B, // var
    CONST  = 0x0C, // const
    GLOBAL = 0x0D, // g_VarName

    // Assignment Tokens
    EQUALS_A     = 0x0E, // =
    EQUALS_ADD_A = 0x0F, // +=
    EQUALS_SUB_A = 0x10, // -=
    EQUALS_MUL_A = 0x11, // *=
    EQUALS_DIV_A = 0x12, // /=
    EQUALS_MOD_A = 0x13, // %=

    // Arithmetic Operators
    ADD = 0x14, // +
    SUB = 0x15, // -
    MUL = 0x16, // *
    DIV = 0x17, // /
    MOD = 0x18, // %
    INC = 0x34, // ++
    DEC = 0x35, // --
    
    // Comparison Operators
    EQUALS     = 0x19, // ==
    NOT_EQUAL  = 0x1A, // ;=
    LESS       = 0x1B, // <
    GREATER    = 0x1C, // >
    LESS_EQ    = 0x1D, // <=
    GREATER_EQ = 0x1E, // >=

    // Logic Operators
    AND = 0x1F, // &&
    OR  = 0x20, // ||
    NOT = 0x21, // ;

    // Grouping
    SPACING = 0x22, // 
    ENDSPACING = 0x23, // 
    LPAREN = 0x24, // (
    RPAREN = 0x25, // )
    LBRACE = 0x24, // {
    RBRACE = 0x25, // }

    // Keywords
    IF       = 0x26, // if
    ELSE_IF  = 0x27, // elseif
    ELSE     = 0x28, // else
    WHEN     = 0x29, // when
    RETURN   = 0x2A, // return   
    FUNCTION = 0x2B, // function
    PREVIOUS = 0x2C, // previous
    AWAIT    = 0x2D, // await
    NEXT     = 0x2E, // next
    CLASS    = 0x2F, // class
    ASYNC    = 0x30, // async
    
    // Others
    COMMA = 0x31, // ,
    DOT   = 0x32, // .
    COLON = 0x33, // :
};

inline std::string TokenToString(Tokens token) {
    switch (token) {
        case UNKNOWN:     return "UNKNOWN";
        case END_OF_FILE: return "END_OF_FILE";
        case END_LINE:    return "END_LINE";
        case DEBUG:       return "DEBUG";
        case END_LINE_2:  return "END_LINE_2";
        case STRING:      return "STRING";
        case INT:         return "INT";
        case FLOAT:       return "FLOAT";
        case FRACTION:    return "FRACTION";
        case BOOL:        return "BOOL";
        case NIL:         return "NIL";
        case IDENT:       return "IDENT";
        case VAR:         return "VAR";
        case CONST:       return "CONST";
        case GLOBAL:      return "GLOBAL";
        case EQUALS_A:    return "EQUALS_A";
        case EQUALS_ADD_A:return "EQUALS_ADD_A";
        case EQUALS_SUB_A:return "EQUALS_SUB_A";
        case EQUALS_MUL_A:return "EQUALS_MUL_A";
        case EQUALS_DIV_A:return "EQUALS_DIV_A";
        case EQUALS_MOD_A:return "EQUALS_MOD_A";
        case ADD:         return "ADD";
        case SUB:         return "SUB";
        case MUL:         return "MUL";
        case DIV:         return "DIV";
        case MOD:         return "MOD";
        case INC:         return "INC";
        case DEC:         return "DEC";
        case EQUALS:      return "EQUALS";
        case NOT_EQUAL:   return "NOT_EQUAL";
        case LESS:        return "LESS";
        case GREATER:     return "GREATER";
        case LESS_EQ:     return "LESS_EQ";
        case GREATER_EQ:  return "GREATER_EQ";
        case AND:         return "AND";
        case OR:          return "OR";
        case NOT:         return "NOT";
        case SPACING:     return "SPACING";
        case ENDSPACING:  return "ENDSPACING";
        case LBRACE:      return "LBRACE";
        case RBRACE:      return "RBRACE";
        case IF:          return "IF";
        case ELSE_IF:     return "ELSE_IF";
        case ELSE:        return "ELSE";
        case WHEN:        return "WHEN";
        case RETURN:      return "RETURN";
        case FUNCTION:    return "FUNCTION";
        case PREVIOUS:    return "PREVIOUS";
        case AWAIT:       return "AWAIT";
        case NEXT:        return "NEXT";
        case CLASS:       return "CLASS";
        case ASYNC:       return "ASYNC";
        case COMMA:       return "COMMA";
        case DOT:         return "DOT";
        case COLON:       return "COLON";
        default:          return "UNKNOWN";
    }
}