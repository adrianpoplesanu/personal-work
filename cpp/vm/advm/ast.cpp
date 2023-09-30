#include "ast.h"

std::string ASTNode::toString() {
    return "unimplemented in subclass";
}

std::string ASTNode::inspect() {
    return "unimplemented in subclass";
}

ASTProgram::ASTProgram() {
    //...
}

ASTProgram::~ASTProgram() {
    for (std::vector<ASTNode*>::iterator it = statements.begin() ; it != statements.end(); ++it) {
        ASTNode *node = *it;
        free_memory_ASTNode(node);
    }
}

void ASTProgram::reset() {
    for (std::vector<ASTNode*>::iterator it = statements.begin() ; it != statements.end(); ++it) {
        ASTNode *node = *it;
        free_memory_ASTNode(node);
    }
    statements.clear();
}

std::string ASTProgram::toString() {
    return "AstProgram";
}

std::string ASTProgram::inspect() {
    return "AstProgram";
}

ASTExpressionStatement::ASTExpressionStatement() {
    type = AT_EXPRESSION_STATEMENT;
}

ASTExpressionStatement::ASTExpressionStatement(Token t) {
    type = AT_EXPRESSION_STATEMENT;
    token = t;
}

ASTExpressionStatement::ASTExpressionStatement(Token t, ASTNode* e) {
    type = AT_EXPRESSION_STATEMENT;
    token = t;
    expression = e;
}

ASTExpressionStatement::~ASTExpressionStatement() {
    free_memory_ASTNode(expression);
}

std::string ASTExpressionStatement::toString() {
    return "ASTExpressionStatement";
}

std::string ASTExpressionStatement::inspect() {
    return "ASTExpressionStatement";
}

ASTInfixExpression::ASTInfixExpression() {
    type = AT_INFIX_EXPRESSION;
}

ASTInfixExpression::ASTInfixExpression(Token t) {
    type = AT_INFIX_EXPRESSION;
    token = t;
}

ASTInfixExpression::ASTInfixExpression(Token t, ASTNode* l, ASTNode* r, std::string op) {
    token = t;
    left = l;
    right = r;
    operand = op;
}

std::string ASTInfixExpression::toString() {
    return "ASTInfixExpression";
}

std::string ASTInfixExpression::inspect() {
    return "ASTInfixExpression";
}

ASTIdentifier::ASTIdentifier() {
    // ...
}

ASTIdentifier::ASTIdentifier(Token t, std::string val) {
    type = AT_IDENTIFIER;
    ref_count = 0;
    token = t;
    value = val;
}

std::string ASTIdentifier::toString() {
    return "ASTIdentifier";
}

std::string ASTIdentifier::inspect() {
    return "ASTIdentifier";
}

ASTInteger::ASTInteger() {
    type = AT_INTEGER;
}

ASTInteger::ASTInteger(Token t) {
    type = AT_INTEGER;
    token = t;
}

ASTInteger::ASTInteger(Token t, int v) {
    type = AT_INTEGER;
    token = t;
    value = v;
}


std::string ASTInteger::toString() {
    return "ASTInteger";
}

std::string ASTInteger::inspect() {
    return "ASTInteger";
}

void Ad_INCREF(ASTNode* node) {
    if (node) {
        node->ref_count++;
    }
}

void Ad_DECREF(ASTNode* node) {
    if (node) {
        node->ref_count--;
    }
}

void free_memory_ASTNode(ASTNode* node) {
    if (node == NULL) return;
    if (node->ref_count > 0) return;
    switch(node->type)  {
        case AT_PROGRAM:
            delete (ASTProgram*) node;
        break;
        case AT_EXPRESSION_STATEMENT:
            delete (ASTExpressionStatement*) node;
        break;
        case AT_IDENTIFIER:
            delete (ASTIdentifier*) node;
        break;
        case AT_INTEGER:
            delete (ASTInteger*) node;
        break;
        case AT_INFIX_EXPRESSION:
            delete (ASTInfixExpression*) node;
        break;
        case AT_PREFIX_EXPRESSION:
            delete (ASTPrefixExpression*) node;
        break;
        case AT_LET_STATEMENT:
            delete (ASTLetStatement*) node;
        break;
        case AT_RETURN_STATEMENT:
            delete (ASTReturnStatement*) node;
        break;
        case AT_FUNCTION_STATEMENT:
            delete (ASTFunctionStatement*) node;
        break;
        case AT_DEF_STATEMENT:
            delete (ASTDefStatement*) node;
        break;
        case AT_WHILE_STATEMENT:
            delete (ASTWhileStatement*) node;
        break;
        case AT_FOR_STATEMENT:
            delete (ASTForStatement*) node;
        break;
        case AT_IF_STATEMENT:
            delete (ASTIfStatement*) node;
        break;
    }
}