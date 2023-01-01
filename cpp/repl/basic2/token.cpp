#include "token.h"

std::string Token::toString() {
    return "Token [" + tokenTypeMap[type] + "] <" + tokenLiteral + ">";
}