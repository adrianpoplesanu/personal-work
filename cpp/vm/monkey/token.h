#ifndef __TOKEN_H
#define __TOKEN_H

#include <iostream>

enum TokenType {
    TT_UNDEFINED,
    TT_INT,
    TT_PLUS
};

class Token {
private:
    std::string stringLiteral;
    TokenType type;
};

#endif