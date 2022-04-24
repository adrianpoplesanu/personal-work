#ifndef __TOKEN_H
#define __TOKEN_H

#include <iostream>
#include <map>

enum TokenType {
    TT_UNDEFINED,
    TT_SUM,
    TT_MINUS,
    TT_MULTIPLY,
    TT_DIVIDE,
    TT_BIGNUMBER,
    TT_LPAREN,
    TT_RPAREN,
    TT_SEMICOLON,
    TT_IDENT,
    TT_ASSIGN,
    TT_EQ,
    TT_NOT_EQ,
    TT_LT,
    TT_GT,
    TT_LTE,
    TT_GTE,
    TT_TRUE,
    TT_FALSE,
    TT_IF,
    TT_LET
};

std::map<TokenType, std::string> token_type_converter = {
    {TT_UNDEFINED, "UNDEFINED"},
    {TT_SUM, "SUM"},
    {TT_MINUS, "MINUS"},
    {TT_MULTIPLY, "MULTIPLY"},
    {TT_DIVIDE, "DIVIDE"},
    {TT_BIGNUMBER, "BIGNUMBER"},
    {TT_LPAREN, "LPAREN"},
    {TT_RPAREN, "RPAREN"},
    {TT_SEMICOLON, "SEMICOLON"},
    {TT_IDENT, "IDENTIFIER"},
    {TT_ASSIGN, "ASSIGN"},
    {TT_EQ, "EQ"},
    {TT_NOT_EQ, "NOT_EQ"},
    {TT_LT, "LT"},
    {TT_GT, "GT"},
    {TT_LTE, "LTE"},
    {TT_GTE, "GTE"},
    {TT_TRUE, "TRUE"},
    {TT_FALSE, "FALSE"},
    {TT_IF, "IF"},
    {TT_LET, "LET"}
};

std::map<std::string, TokenType> keywords = {
    {"true", TT_TRUE},
    {"false", TT_FALSE},
    {"if", TT_IF},
    {"let", TT_LET}
};

class Token {
    private:
        std::string tokenLiteral;
        TokenType type;

    public:
        Token();
        ~Token();
        std::string getLiteral();
        void setLiteral(std::string);
        TokenType getType();
        void setType(TokenType);
        std::string toString();
};

#endif