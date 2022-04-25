#ifndef __LEXER_H
#define __LEXER_H

#include <iostream>
#include "token.h"
#include "token.cpp"

class Lexer {
    private:
        std::string source;
        int position;
        int readPosition;
        char current_char;
    public:
        Lexer();
        ~Lexer();
        void load(std::string);
        void skipWhitespaces();
        void nextChar();
        bool isDigit();
        bool isLetter();
        bool isFloatDot();
        void readChar();
        std::string readBigNumber();
        Token nextToken();
};

#endif