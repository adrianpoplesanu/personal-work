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

void Lexer::readChar() {
    if (readPosition >= source.length()) {
        current_char = 0;
    } else {
        current_char = source[readPosition];
    }
    position = readPosition;
    readPosition++;
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
        default:
            if (isLetter()) {

            } else if (isDigit()) {
                read_next_char = false;
                std::string literal = readBigNumber();
                result.setLiteral(literal);
                result.setType(TT_BIGNUMBER);
            } else {
                result.setLiteral("bla bla bla");
                result.setType(TT_UNDEFINED);
            }
        break;
    }
    if (read_next_char) readChar();
    return result;
}