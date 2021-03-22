#include "token.h"

Token::Token() {
    BuildTokenTypeMap();
}

Token::Token(TokenType tt) {
    token_type = tt;
    BuildTokenTypeMap();
}

Token::~Token() {

}

void Token::BuildTokenTypeMap() {
    token_type_map.insert(pair<TokenType, string>(ILLEGAL, "ILLEGAL")); // todo: a python script that fills this in
}

void Token::BuildKeywordsMap() {
    
}

TokenType Token::GetTokenType() {
    return token_type;
}

void Token::SetTokenType(TokenType tt) {
    token_type = tt;
}