#ifndef __PARSER_H
#define __PARSER_H

#include <map>
#include "lexer.h"
#include "token.h"
#include "ast.h"

enum PrecedenceType {
    PT_LOWEST,
    PT_SUM,
    PT_MULTIPLY,
    PT_CALL
};

std::map<TokenType, PrecedenceType> precedences = {
    {TT_SUM, PT_SUM},
    {TT_MINUS, PT_SUM},
    {TT_MULTIPLY, PT_MULTIPLY},
    {TT_DIVIDE, PT_MULTIPLY},
    {TT_LPAREN, PT_CALL}
};

class Parser {
    typedef AstNode* (Parser::*PrefixCallback)();
    typedef AstNode* (Parser::*InfixCallback)(AstNode*);

    private:
        std::map<TokenType, PrefixCallback> prefixParseFns;
        std::map<TokenType, InfixCallback> infixParseFns;

    public:
        Parser();
        ~Parser();
};

#endif
