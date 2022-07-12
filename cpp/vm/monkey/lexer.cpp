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
    readChar();
}

void Lexer::readChar() {
    if (readPosition >= source.length()) currentChar = 0;
    else {
        currentChar = source.at(readPosition);
    }
    position = readPosition;
    readPosition++;
}

void Lexer::skipWhitespaces() {
    while (currentChar == ' ' || currentChar == '\t' || currentChar == '\r' || currentChar == '\n') readChar();
}

bool Lexer::isEOF() {
    return currentChar == 0;
}

Token Lexer::nextToken() {
    bool readNextChar = true;
    Token token;
    skipWhitespaces();
    switch (currentChar) {
        case '+':
        token.stringLiteral = '+';
        token.type = TokenType::TT_PLUS;
        break;
        default:
        token.stringLiteral = currentChar;
        token.type = TokenType::TT_UNDEFINED;
        break;
    }
    if (readNextChar) readChar();
    return token;
}