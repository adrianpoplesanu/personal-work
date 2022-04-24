#include "token.h"

Token::Token() {

}

Token::~Token() {

}

std::string Token::getLiteral() {
    return tokenLiteral;
}

void Token::setLiteral(std::string tokLiteral) {
    tokenLiteral = tokLiteral;
}

TokenType Token::getType() {
    return type;
}

void Token::setType(TokenType tokenType) {
    type = tokenType;
}

std::string Token::toString() {
    return "Token [" + token_type_converter[type] + "] <" + tokenLiteral + ">";
}