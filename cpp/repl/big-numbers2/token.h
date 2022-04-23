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
    TT_RPAREN
};

std::map<TokenType, std::string> token_type_converter = {
    {TT_UNDEFINED, "UNDEFINED"},
    {TT_SUM, "SUM"},
    {TT_MINUS, "MINUS"},
    {TT_MULTIPLY, "MULTIPLY"},
    {TT_DIVIDE, "DIVIDE"},
    {TT_BIGNUMBER, "BIGNUMBER"},
    {TT_LPAREN, "LPAREN"},
    {TT_RPAREN, "RPAREN"}
};

std::map<std::string, TokenType> keywords = {
    {"if", TT_UNDEFINED}
};

class Token {
    private:
        std::string tokenLiteral;
        TokenType type;

    public:
        Token();
        ~Token();
        std::string GetLiteral();
        void SetLiteral(std::string);
        TokenType GetType();
        void SetType(TokenType);
        std::string toString();
};

#endif