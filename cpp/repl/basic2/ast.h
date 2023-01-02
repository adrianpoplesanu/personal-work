#ifndef __AST_H
#define __AST_H

#include "token.h"
#include <vector>

enum ASTNodeType {
    AST_PROGRAM,
    AST_EXPRESSION_STATEMENT,
    AST_INTEGER,
    AST_INFIX_EXPRESSION
};

class ASTNode {
public:
    ASTNodeType type;
    Token token;
    int ref_count;
};

class ASTProgram : public ASTNode {
public:
    std::vector<ASTNode*> statements;

    ASTProgram();
};

class ASTExpressionStatement : public ASTNode {
public:
    ASTNode* expression;

    ASTExpressionStatement(Token);
};

class ASTInfixExpression : public ASTNode {
public:
    ASTNode* left;
    ASTNode* right;
    std::string _operator;

    ASTInfixExpression(Token);
};

class ASTInteger : public ASTNode {
public:
    int value;

    ASTInteger(Token);
};

#endif
