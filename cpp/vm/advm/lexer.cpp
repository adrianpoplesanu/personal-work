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

bool Lexer::isDigit() {
    return '0' <= currentChar && currentChar <= '9'; 
}

bool Lexer::isLetter() {
    return ('a' <= currentChar && currentChar <= 'z') || ('A' <= currentChar && currentChar <= 'Z') || currentChar == '_';
}

std::string Lexer::readIdentifier() {
    int start = position;
    while (isLetter()) {
        readChar();
    }
    return source.substr(start, position - start);
}

std::string Lexer::readNumber() {
    int start = position;
    while (isDigit()) {
        readChar();
    }
    return source.substr(start, position - start);
}

Token Lexer::nextToken() {
    bool readNextChar = true;
    Token token;
    skipWhitespaces();
    switch (currentChar) {
        case '+':
            token.stringLiteral = '+';
            token.type = TT_PLUS;
            break;
        case '-':
            token.stringLiteral = '-';
            token.type = TT_MINUS;
            break;
        case '*':
            token.stringLiteral = '*';
            token.type = TT_MULTIPLY;
            break;
        case '/':
            token.stringLiteral = '/';
            token.type = TT_DIVIDE;
            break;
        default:
            if (isLetter()) {
                readNextChar = false;
                token.stringLiteral = readIdentifier();
                token.type = TT_IDENT;
            } else if (isDigit()) {
                readNextChar = false;
                token.stringLiteral = readNumber();
                token.type = TT_INT;
            } else {
                token.stringLiteral = currentChar;
                token.type = TT_UNDEFINED;
            }
            break;
    }
    if (readNextChar) readChar();
    return token;
}