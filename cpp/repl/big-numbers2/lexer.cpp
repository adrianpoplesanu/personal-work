#include "lexer.h"

Lexer::Lexer() {

}

Lexer::~Lexer() {

}

void Lexer::load(std::string s) {
    source = s;
    position = 0;
    readPosition = 0;
    readChar();
}

bool Lexer::isLetter() {
    return ('a' <= current_char && current_char <= 'z') || ('A' <= current_char && current_char <= 'Z')  || current_char == '_';
}

bool Lexer::isDigit() {
    return '0' <= current_char && current_char <= '9';
}

void Lexer::skipWhitespaces() {
    while(current_char == ' ') readChar();
}

std::string Lexer::readBigNumber() {
    int start = position;
    while(isDigit()) {
        readChar();
    }
    return source.substr(start, position - start);
}

std::string Lexer::readLiteral() {
    int start = position;
    while(isLetter()) {
        readChar();
    }
    while(isLetter() || isDigit()) {
        readChar();
    }
    return source.substr(start, position - start);
}

void Lexer::readChar() {
    if (readPosition >= source.length()) {
        current_char = 0;
    } else {
        current_char = source[readPosition];
    }
    position = readPosition;
    readPosition++;
}

TokenType Lexer::lookupKeyword(std::string literal) {
    if (keywords.find(literal) != keywords.end()) return keywords.find(literal)->second;
    return TT_IDENT;
}

Token Lexer::nextToken() {
    Token result;
    bool read_next_char = true;
    skipWhitespaces();
    switch(current_char) {
        case 0:
            result.setLiteral("");
            result.setType(TT_EOF);
        break;
        case '+':
            result.setLiteral("+");
            result.setType(TT_SUM);
        break;
        case '-':
            result.setLiteral("-");
            result.setType(TT_MINUS);
        break;
        case '*':
            result.setLiteral("*");
            result.setType(TT_MULTIPLY);
        break;
        case '/':
            result.setLiteral("/");
            result.setType(TT_DIVIDE);
        break;
        case '{':
            result.setLiteral("{");
            result.setType(TT_LBRACKET);
        break;
        case '}':
            result.setLiteral("}");
            result.setType(TT_RBRACKET);
        break;
        default:
            if (isLetter()) {
                read_next_char = false;
                std::string literal = readLiteral();
                result.setLiteral(literal);
                result.setType(lookupKeyword(literal));
            } else if (isDigit()) {
                read_next_char = false;
                std::string literal = readBigNumber();
                result.setLiteral(literal);
                result.setType(TT_BIGNUMBER);
            } else {
                std::string literal;
                literal.push_back(current_char);
                result.setLiteral(literal);
                result.setType(TT_ILLEGAL);
            }
        break;
    }
    if (read_next_char) readChar();
    return result;
}