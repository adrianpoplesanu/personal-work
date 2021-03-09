#include "token.h"

Token::Token() {

}

Token::Token(TokenType tt) {
    token_type = tt;
}

Token::~Token() {

}

TokenType Token::GetTokenType() {
    return token_type;
}

void Token::SetTokenType(TokenType tt) {
    token_type = tt;
}