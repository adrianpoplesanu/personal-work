#ifndef __LEXER_H
#define __LEXER_H

#include <iostream>
#include "token.h"

class Lexer {
private:
    std::string source;
    int position;
    int readPosition;
    char currentChar;

public:
    void load(std::string);
    void readChar();
    Token nextToken();
    void skipWhitespaces();
    std::string readNumber();
    std::string readIdentifier();
    TokenType lookupIdentifier(std::string);
    char peekChar();
    bool isEOF();
};

#endif