#ifndef __AST_H
#define __AST_H

#include "token.h"
#include <vector>

enum ASTType {
    AT_PROGRAM,
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

class ASTProgram : ASTNode {
public:
    std::vector<ASTNode> statements;

    ASTProgram();
    virtual std::string inspect();
    virtual std::string toString();
    void reset();
};

class ASTExpressionStatement : ASTNode {

};

class ASTInfixExpression : ASTNode {

};

class ASTPrefixExpression : ASTNode {

};

class ASTInteger : ASTNode {
public:
    int value;

    ASTInteger();
    ASTInteger(Token);
    ASTInteger(Token, int);
    virtual std::string inspect();
    virtual std::string toString();

};

class ASTIdentifier : ASTNode {
public:
    std::string value;
};

void Ad_INCREF(ASTNode*);
void Ad_DECREF(ASTNode*);

void free_memory_ASTNode(ASTNode*);

#endif
