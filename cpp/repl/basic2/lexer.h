#ifndef __LEXER_H
#define __LEXER_H

#include <iostream>
#include "token.h"

class Lexer {
public:
    std::string source;
    int readPosition;
    int position;
    char currentChar;

    void load(std::string);
    void readChar();
    Token nextToken();
};

#endif
