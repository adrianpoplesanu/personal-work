#include "token.h"
#include "ast.h"

Token::Token() {
    BuildTokenTypeMap();
    BuildKeywordsMap();
}

Token::Token(TokenType tt) {
    token_type = tt;
    BuildTokenTypeMap();
    BuildKeywordsMap();
}

Token::~Token() {

}

void Token::BuildTokenTypeMap() {
    token_type_map.insert(pair<TokenType, string>(ILLEGAL, "ILLEGAL")); // todo: a python script that fills this in
    token_type_map.insert(pair<TokenType, string>(ILLEGAL, "ILLEGAL"));
    token_type_map.insert(pair<TokenType, string>(IDENT, "IDENT"));
    token_type_map.insert(pair<TokenType, string>(INT, "INT"));
    token_type_map.insert(pair<TokenType, string>(ASSIGN, "ASSIGN"));
    token_type_map.insert(pair<TokenType, string>(PLUS, "PLUS"));
    token_type_map.insert(pair<TokenType, string>(MINUS, "MINUS"));
    token_type_map.insert(pair<TokenType, string>(SLASH, "SLASH"));
    token_type_map.insert(pair<TokenType, string>(ASTERICKS, "ASTERICKS"));
    token_type_map.insert(pair<TokenType, string>(BANG, "BANG"));
    token_type_map.insert(pair<TokenType, string>(LET, "LET"));
    token_type_map.insert(pair<TokenType, string>(RETURN, "RETURN"));
    token_type_map.insert(pair<TokenType, string>(WHILE, "WHILE"));
    token_type_map.insert(pair<TokenType, string>(LPAREN, "LPAREN"));
    token_type_map.insert(pair<TokenType, string>(RPAREN, "RPAREN"));
    token_type_map.insert(pair<TokenType, string>(LBRACE, "LBRACE"));
    token_type_map.insert(pair<TokenType, string>(RBRACE, "RBRACE"));
    token_type_map.insert(pair<TokenType, string>(COLON, "COLON"));
    token_type_map.insert(pair<TokenType, string>(SEMICOLON, "SEMICOLON"));
    token_type_map.insert(pair<TokenType, string>(LT, "LT"));
    token_type_map.insert(pair<TokenType, string>(GT, "GT"));
    token_type_map.insert(pair<TokenType, string>(EQ, "EQ"));
    token_type_map.insert(pair<TokenType, string>(NOT_EQ, "NOT_EQ"));
}

void Token::BuildKeywordsMap() {
    keywords_map.insert(pair<string, TokenType>("fn", FUNCTION));
    keywords_map.insert(pair<string, TokenType>("let", LET));
    keywords_map.insert(pair<string, TokenType>("true", TRUE));
    keywords_map.insert(pair<string, TokenType>("false", FALSE));
    keywords_map.insert(pair<string, TokenType>("if", IF));
    keywords_map.insert(pair<string, TokenType>("else", ELSE));
    keywords_map.insert(pair<string, TokenType>("return", RETURN));
}

TokenType Token::GetTokenType() {
    return token_type;
}

void Token::SetTokenType(TokenType tt) {
    token_type = tt;
}