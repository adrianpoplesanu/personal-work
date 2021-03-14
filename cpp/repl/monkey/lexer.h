#ifndef __LEXER_H
#define __LEXER_H

#include <string>
using namespace std;

class Lexer {
public:
    Lexer();
    ~Lexer();
    void Load(string);
    void ReadChar();
    char NextToken();

private:
    string source;
    int position;
    int readPosition;
    char current_char;
};

#endif