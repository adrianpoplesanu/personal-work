#include "lexer.h"

void Lexer::load(std::string s) {
    source = s;
    position = 0;
    readPosition = 0;
    readChar();
}

void Lexer::readChar() {
    if (readPosition >= source.length()) {
        currentChar = 0;
    } else {
        currentChar = source.at(readPosition);
    }
    position = readPosition;
    readPosition++;
}

Token Lexer::nextToken() {
    Token token;
    token.type = TT_ILLEGAL;
    skipWhitespaces();
    bool needsReadChar = true;
    switch(currentChar) {
        case 0:
            token.type = TT_EOF;
            token.tokenLiteral = "";
        break;
        case '+':
            token.type = TT_PLUS;
            token.tokenLiteral = "+";
        break;
        case '-':
            token.type = TT_MINUS;
            token.tokenLiteral = "-";
        break;
        case '*':
            token.type = TT_MULTIPLY;
            token.tokenLiteral = "*";
        break;
        case '/':
            token.type = TT_DIVIDE;
            token.tokenLiteral = "/";
        break;
        case '(':
            token.type = TT_LPAREN;
            token.tokenLiteral = "(";
        break;
        case ')':
            token.type = TT_RPAREN;
            token.tokenLiteral = ")";
        break;
        case ';':
            token.type = TT_SEMICOLON;
            token.tokenLiteral = ";";
        break;
        default:
            if (isDigit()) {
                int startPos = position;
                while (isDigit()) {
                    readChar();
                }
                token.type = TT_INT;
                token.tokenLiteral = source.substr(startPos, position - startPos);
                needsReadChar = false;
            }
        break;
    }
    if (needsReadChar) {
        readChar();
    }
    return token;
}

std::string Lexer::readNumber() {
    std::string result = "";
    return result;
}

bool Lexer::isDigit() {
    return currentChar >= '0' && currentChar <= '9';  
}

void Lexer::skipWhitespaces() {
    while (currentChar == ' ' || currentChar == '\t' || currentChar == '\r' || currentChar == '\n') {
        readChar();
    }
}