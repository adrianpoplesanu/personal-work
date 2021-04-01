#include "lexer.h"
#include "token.h"
#include <iostream>
#include <string>
using namespace std;

Lexer::Lexer() {
    position = 0;
    readPosition = 0;
}

Lexer::~Lexer() {

}

void Lexer::Load(string s) {
    position = 0;
    readPosition = 0;
    source = s;
    ReadChar();
}

void Lexer::ReadChar() {
    if (readPosition < source.length()) {
        current_char = source[readPosition];
    } else {
        current_char = 0;
    }
    position = readPosition;
    readPosition++;
}

Token Lexer::NextToken() {
    Token token;
    SkipWhitespace();
    switch(current_char) {
        case 0:
            token.SetTokenType(END);
            token.literal = "";
            //return token;
        break;
        case '=':
            token.SetTokenType(ASSIGN);
            token.literal = "=";
            //return token;
        break;
        case ';':
            token.SetTokenType(SEMICOLON);
            token.literal = ";";
            //return token;
        break;
        default:
            if (IsLetter()) {
                string ident = ReadIdentifier();
                token.SetTokenType(IDENT);
                token.literal = ident;
                //return token;
            } else if (IsDigit()) {
                token.SetTokenType(INT);
                token.literal = current_char;
            } else {
                token.SetTokenType(ILLEGAL);
                token.literal = current_char;
            }
        break;
    }
    if (token.token_type != IDENT) ReadChar();
    return token;
}

void Lexer::SkipWhitespace() {
    while(current_char == ' ') ReadChar();
}

bool Lexer::IsLetter() {
    return (('a' <= current_char) && (current_char <= 'z')) || (('A' <= current_char) && (current_char <= 'Z')) || (current_char == '_');
}

bool Lexer::IsDigit() {
    return ('0' <= current_char) && (current_char <= '9');
}

string Lexer::ReadIdentifier() {
    int start = position;
    while (IsLetter()) {
        ReadChar();
    }
    return source.substr(start, position - start);
}