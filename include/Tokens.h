// Long ahh tokens list, using hexadecimal to look cool
enum Tokens {
    // Special Tokens
    END_OF_FILE = 0x00, // Idfk
    END_LINE    = 0x01, // !
    DEBUG       = 0x02, // ?
    SPACE       = 0x03, //  

    // Datatype Tokens
    STRING   = 0x04, // "String"
    INT      = 0x05, // 10
    FLOAT    = 0x06, // 10.5
    FRACTION = 0x07, // 1/2
    BOOL     = 0x08, // true

    // Variable Tokens
    IDENT  = 0x09, // VarName
    VAR    = 0x0A, // var
    CONST  = 0x0B, // const
    GLOBAL = 0x0C, // g_VarName

    // Assignment Tokens
    EQUALS_A     = 0x0D, // =
    EQUALS_ADD_A = 0x0E, // +=
    EQUALS_SUB_A = 0x0F, // -=
    EQUALS_MUL_A = 0x10, // *=
    EQUALS_DIV_A = 0x11, // /=
    EQUALS_MOD_A = 0x12, // %=

    // Arithmetic Operators
    ADD = 0x13, // +
    SUB = 0x14, // -
    MUL = 0x15, // *
    DIV = 0x16, // /
    MOD = 0x17, // %

    // Comparison Operators
    EQUALS     = 0x18, // ==
    NOT_EQUALS = 0x19, // !=
    LESS       = 0x1A, // 
    GREATER    = 0x1B, // >
    LESS_EQ    = 0x1C, // <=
    GREATER_EQ = 0x1D, // >=

    // Logic Operators
    AND = 0x1E, // &&
    OR  = 0x1F, // ||
    NOT = 0x20, // ;

    // Grouping
    LPAREN = 0x21, // (
    RPAREN = 0x22, // )
    LBRACE = 0x23, // {
    RBRACE = 0x24, // }

    // Keywords
    IF       = 0x25, // if
    ELSE_IF  = 0x26, // elseif
    ELSE     = 0x27, // else
    WHEN     = 0x28, // when
    RETURN   = 0x29, // return
    FUNCTION = 0x2A, // function
    PREVIOUS = 0x2B, // previous
    AWAIT    = 0x2C, // await
    NEXT     = 0x2D, // next
    CLASS    = 0x2E, // class
    ASYNC    = 0x2F, // async

    // Others
    COMMA = 0x30, // ,
    DOT   = 0x31, // .
    COLON = 0x32, // :
};