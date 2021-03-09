#ifndef __TOKEN_H
#define __TOKEN_H

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
    NOT_EQ
};

class Token {
private:
    TokenType token_type;
public:
    Token();
    Token(TokenType);
    ~Token();
    TokenType GetTokenType();
    void SetTokenType(TokenType);
};

#endif