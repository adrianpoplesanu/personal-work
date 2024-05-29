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

char Lexer::peekChar() {
    return source.at(readPosition);
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

TokenType Lexer::lookupKeyword(std::string literal) {
    if (keywords.find(literal) != keywords.end()) {
        return keywords.at(literal);
    }
    return TT_IDENT;
}

Token Lexer::nextToken() {
    bool readNextChar = true;
    Token token;
    skipWhitespaces();
    switch (currentChar) {
        case 0:
            token.stringLiteral = "";
            token.type = TT_EOF;
            break;
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
        case '(':
            token.stringLiteral = '(';
            token.type = TT_LPAREN;
            break;
        case ')':
            token.stringLiteral = ')';
            token.type = TT_RPAREN;
            break;
        case '{':
            token.stringLiteral = '{';
            token.type = TT_LBRACE;
            break;
        case '}':
            token.stringLiteral = '}';
            token.type = TT_RBRACE;
            break;
        case ';':
            token.stringLiteral = ';';
            token.type = TT_SEMICOLON;
            break;
        case '>':
            if (peekChar() == '=') {
                readChar();
                token.stringLiteral = ">=";
                token.type = TT_GTE;
            } else {
                token.stringLiteral = '>';
                token.type = TT_GT;
            }
            break;
        case '<':
            if (peekChar() == '=') {
                readChar();
                token.stringLiteral = "<=";
                token.type = TT_LTE;
            } else {
                token.stringLiteral = '<';
                token.type = TT_LT;
            }
            break;
        case '=':
            if (peekChar() == '=') {
                readChar();
                token.stringLiteral = "==";
                token.type = TT_EQUALS;
            } else {
                token.stringLiteral = '=';
                token.type = TT_ASSIGN;
            }
            break;
        case '!':
            break;
        default:
            if (isLetter()) {
                readNextChar = false;
                token.stringLiteral = readIdentifier();
                token.type = lookupKeyword(token.stringLiteral);
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