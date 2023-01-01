#ifndef __TOKEN_H
#define __TOKEN_H

#include <map>

enum TokenTypeEnum {
    TT_ILLEGAL,
    TT_EOF,
    TT_INT,
    TT_PLUS,
    TT_MINUS,
    TT_MULTIPLY,
    TT_DIVIDE,
    TT_LPAREN,
    TT_RPAREN
};

std::map<TokenTypeEnum, std::string> tokenTypeMap = {
    {TT_ILLEGAL, "ILLEGAL"},
    {TT_EOF, "EOF"},
    {TT_INT, "INT"},
    {TT_PLUS, "PLUS"},
    {TT_MINUS, "MINUS"},
    {TT_MULTIPLY, "MULTIPLY"},
    {TT_DIVIDE, "DIVIDE"},
    {TT_LPAREN, "LPAREN"},
    {TT_RPAREN, "RPAREN"}
};

std::map<std::string, TokenTypeEnum> keywords = {

};

class Token {
public:
    TokenTypeEnum type;
    std::string tokenLiteral;

    std::string toString();
};

#endif
