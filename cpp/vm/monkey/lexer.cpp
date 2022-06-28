#include "lexer.h"

Lexer::Lexer() {
    currentChar = 0;
    position = 0;
    readPosition = 0;
    source = "";
}

void Lexer::load(std::string s) {
    source = s;
    position = 0;
    readPosition = 0;
    currentChar = 0;
}