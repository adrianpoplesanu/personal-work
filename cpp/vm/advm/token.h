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
    TT_LET,
    TT_RETURN,
    TT_FUNCTION,
    TT_DEF,
    TT_IF,
    TT_ELSE,
    TT_LPAREN,
    TT_RPAREN,
    TT_LBRACE,
    TT_RBRACE,
    TT_TRUE,
    TT_FALSE,
    TT_WHILE,
    TT_FOR,
    TT_BREAK,
    TT_CONTINUE,
    TT_SINGLECOMMENT,
    TT_MULTICOMMENT,
    TT_SEMICOLON,
    TT_GT,
    TT_LT,
    TT_GTE,
    TT_LTE,
    TT_EQUALS,
    TT_NOT_EQUALS
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
    {TT_LET, "LET"},
    {TT_RETURN, "RETURN"},
    {TT_FUNCTION, "FUNCTION"},
    {TT_DEF, "DEF"},
    {TT_IF, "IF"},
    {TT_ELSE, "ELSE"},
    {TT_LPAREN, "LPAREN"},
    {TT_RPAREN, "RPAREN"},
    {TT_LBRACE, "LBRACE"},
    {TT_RBRACE, "RBRACE"},
    {TT_TRUE, "TRUE"},
    {TT_FALSE, "FALSE"},
    {TT_WHILE, "WHILE"},
    {TT_FOR, "FOR"},
    {TT_SEMICOLON, "SEMICOLON"},
    {TT_GT, "GREATERTHAN"},
    {TT_LT, "LOWERTHAN"},
    {TT_GTE, "GREATERTHANEQUAL"},
    {TT_LTE, "LOWERTHANEQUAL"},
    {TT_EQUALS, "EQUALS"},
    {TT_NOT_EQUALS, "NOTEQUALS"}
};

std::map<std::string, TokenType> keywords = {
    {"let", TT_LET},
    {"return", TT_RETURN},
    {"fun", TT_FUNCTION},
    {"def", TT_DEF},
    {"if", TT_IF},
    {"else", TT_ELSE},
    {"true", TT_TRUE},
    {"false", TT_FALSE},
    {"while", TT_WHILE},
    {"for", TT_FOR}
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