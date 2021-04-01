#ifndef __TOKEN_H
#define __TOKEN_H

#include <map>
#include <string>
using namespace std;

enum TokenType {
    ILLEGAL,
    IDENT,
    INT,
    ASSIGN,
    PLUS,
    MINUS,
    SLASH,
    ASTERICKS,
    BANG,
    LET,
    RETURN,
    WHILE,
    LPAREN,
    RPAREN,
    LBRACE,
    RBRACE,
    COLON,
    SEMICOLON,
    LT,
    GT,
    EQ,
    NOT_EQ,
    FUNCTION,
    TRUE,
    FALSE,
    IF,
    ELSE,
    END
};

class Token {
private:
    void BuildTokenTypeMap();
    void BuildKeywordsMap();
public:
    Token();
    Token(TokenType);
    ~Token();
    TokenType GetTokenType();
    void SetTokenType(TokenType);
    map<TokenType, string> token_type_map;
    map<string, TokenType> keywords_map;
    TokenType token_type;
    string literal;
    string ToString();
};

#endif