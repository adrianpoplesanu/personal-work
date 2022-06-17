#ifndef __AST_H
#define __AST_H

#include "token.h"

enum ASTType {
    AT_EXPRESSION_STATEMENT,
    AT_IDENTIFIER,
    AT_INTEGER,
    AT_INFIX_EXPRESSION,
    AT_PREFIX_EXPRESSSION
};

class ASTNode {
public:
    Token token;
    ASTType type;
    int ref_count;

    virtual std::string inspect();
    virtual std::string toString();
};

class ASTExpressionStatement : ASTNode {

};

#endif
