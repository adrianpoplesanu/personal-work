#ifndef __LEXER_H
#define __LEXER_H

#include <iostream>

class Lexer {
    private:
        std::string source;
        int position;
        int readPosition;
        char current_char;
    public:
        Lexer();
        ~Lexer();
        void Load(std::string);
        void NextChar();
};

#endif