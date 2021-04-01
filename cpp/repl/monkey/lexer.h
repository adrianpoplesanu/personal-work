#ifndef __LEXER_H
#define __LEXER_H

#include <string>
#include "token.h"
using namespace std;

class Lexer {
public:
    Lexer();
    ~Lexer();
    void Load(string);
    void ReadChar();
    Token NextToken();
    void SkipWhitespace();
    bool IsLetter();
    bool IsDigit();
    string ReadIdentifier();

private:
    string source;
    int position;
    int readPosition;
    char current_char;
};

#endif