#include "lexer.h"

void Lexer::load(std::string s) {
    source = s;
    position = 0;
    readPosition = 0;
    readChar();
}

void Lexer::readChar() {
    if (readPosition >= source.size()) {
        currentChar = 0;
    } else {
        currentChar = source.at(readPosition);
        position = readPosition;
        readPosition++;
    }
}

Token Lexer::nextToken() {
    Token token;
    token.type = TT_ILLEGAL;
    return token;
}