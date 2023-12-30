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
    AT_PREFIX_EXPRESSION,
    AT_LET_STATEMENT,
    AT_RETURN_STATEMENT,
    AT_FUNCTION_STATEMENT,
    AT_DEF_STATEMENT,
    AT_WHILE_STATEMENT,
    AT_FOR_STATEMENT,
    AT_IF_STATEMENT
};

class ASTNode {
public:
    Token token;
    ASTType type;
    int ref_count;

    virtual std::string inspect();
    virtual std::string toString();
};

class ASTProgram : public ASTNode {
public:
    std::vector<ASTNode*> statements;

    ASTProgram();
    ~ASTProgram();
    virtual std::string inspect();
    virtual std::string toString();
    void reset();
};

class ASTExpressionStatement : public ASTNode {
public:
    ASTNode* expression;

    ASTExpressionStatement();
    ASTExpressionStatement(Token);
    ASTExpressionStatement(Token, ASTNode*);
    ~ASTExpressionStatement();
    virtual std::string inspect();
    virtual std::string toString();
};

class ASTInfixExpression : public ASTNode {
public:
    ASTNode* left;
    ASTNode* right;
    std::string _operator;

    ASTInfixExpression();
    ASTInfixExpression(Token);
    ASTInfixExpression(Token, ASTNode*, ASTNode*, std::string);
    ~ASTInfixExpression();
    virtual std::string inspect();
    virtual std::string toString();
};

class ASTPrefixExpression : public ASTNode {
public:
    ASTNode* right;
    std::string operand;
};

class ASTLetStatement : public ASTNode {

};

class ASTReturnStatement : public ASTNode {
    
};

class ASTFunctionStatement : public ASTNode {

};

class ASTDefStatement : public ASTNode {

};

class ASTInteger : public ASTNode {
public:
    int value;

    ASTInteger();
    ASTInteger(Token);
    ASTInteger(Token, int);
    virtual std::string inspect();
    virtual std::string toString();

};

class ASTIdentifier : public ASTNode {
public:
    std::string value;

    ASTIdentifier();
    ASTIdentifier(Token, std::string);
    virtual std::string inspect();
    virtual std::string toString();
};

class ASTWhileStatement : public ASTNode {
public:

    ASTWhileStatement();
    ASTWhileStatement(Token);
    virtual std::string inspect();
    virtual std::string toString();
};

class ASTForStatement : public ASTNode {
public:

    ASTForStatement();
    ASTForStatement(Token);
    virtual std::string inspect();
    virtual std::string toString();
};

class ASTIfStatement : public ASTNode {
public:

    ASTIfStatement();
    ASTIfStatement(Token);
    virtual std::string inspect();
    virtual std::string toString();
};

void Ad_INCREF(ASTNode*);
void Ad_DECREF(ASTNode*);

void free_memory_ASTNode(ASTNode*);

#endif
