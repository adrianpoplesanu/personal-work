#ifndef __TOKEN_H
#define __TOKEN_H

#include <iostream>
#include <map>

enum TokenType {
    TT_UNDEFINED,
    TT_EOF,
    TT_INT,
    TT_PLUS,
    TT_MINUS,
    TT_MULTIPLY,
    TT_DIVIDE,
    TT_IDENT,
    TT_ASSIGN,
    TT_LET
};

std::map<TokenType, std::string> tokenTypeConverter = {
    {TT_UNDEFINED, "UNDEFINED"},
    {TT_EOF, "EOF"},
    {TT_INT, "INT"},
    {TT_PLUS, "PLUS"},
    {TT_MINUS, "MINUS"},
    {TT_MULTIPLY, "MULTIPLY"},
    {TT_DIVIDE, "DIVIDE"},
    {TT_IDENT, "IDENT"},
    {TT_ASSIGN, "ASSIGN"},
    {TT_LET, "LET"}
};

class Token {
public:
    std::string stringLiteral;
    TokenType type;

    Token();
    Token(TokenType);
    Token(TokenType, std::string);
    std::string toString();
};

#endif