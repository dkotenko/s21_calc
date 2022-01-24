#ifndef TYPES_H
#define TYPES_H

#define OPERANDS "+-/*^"

enum operand {
    PLUS,
    MINUS,
    DIV,
    MULT,
    MOD,
    POW,
    VAL,
    OPERANDS_NUM
};

enum function {
    SIN,
    COS,
    TAN,
    ASIN,
    ACOS,
    ATAN,
    LOG,
    LN,
    FUNCTIONS_NUM
};

enum bracket {
    LBRACKET,
    RBRACKET,
    BRACKETS_NUM
};

enum token_type {
    OPERAND,
    VALUE,
    BRACKET,
    FUNCTION,
    TYPES_NUM
};

#endif