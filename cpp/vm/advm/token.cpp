#include "token.h"

Token::Token() {
    type = TT_UNDEFINED;
};

Token::Token(TokenType t) {
    type = t;
}

Token::Token(TokenType t, std::string l) {
    type = t;
    stringLiteral = l;
}

std::string Token::toString() {
    return "Token [" + tokenTypeConverter[type] + "] <" + stringLiteral + ">";
}