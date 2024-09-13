#include "ast.h"

std::string ASTNode::toString() {
    return "unimplemented in subclass";
}

std::string ASTNode::inspect() {
    return "unimplemented in subclass";
}

ASTProgram::ASTProgram() {
    type = AT_PROGRAM;
    ref_count = 0;
}

ASTProgram::~ASTProgram() {
    for(std::vector<ASTNode*>::iterator it = statements.begin() ; it != statements.end(); ++it) {
        ASTNode *node = *it;
        free_memory_ASTNode(node);
    }
}

void ASTProgram::reset() {
    for(std::vector<ASTNode*>::iterator it = statements.begin() ; it != statements.end(); ++it) {
        ASTNode *node = *it;
        free_memory_ASTNode(node);
    }
    statements.clear();
}

std::string ASTProgram::toString() {
    std::string out = "";
    out += "AstProgram\n";
    for (ASTNode* it : statements) {
        out += it->toString();
    }
    return out;
}

std::string ASTProgram::inspect() {
    return "AstProgram\n";
}

ASTExpressionStatement::ASTExpressionStatement() {
    type = AT_EXPRESSION_STATEMENT;
    ref_count = 0;
}

ASTExpressionStatement::ASTExpressionStatement(Token t) {
    type = AT_EXPRESSION_STATEMENT;
    ref_count = 0;
    token = t;
}

ASTExpressionStatement::ASTExpressionStatement(Token t, ASTNode* e) {
    type = AT_EXPRESSION_STATEMENT;
    ref_count = 0;
    token = t;
    expression = e;
}

ASTExpressionStatement::~ASTExpressionStatement() {
    free_memory_ASTNode(expression);
}

std::string ASTExpressionStatement::toString() {
    if (expression == NULL) {
        return "ASTExpressionStatement[None]\n";
    }
    return "ASTExpressionStatement[" + expression->toString() + "]\n";
}

std::string ASTExpressionStatement::inspect() {
    return "ASTExpressionStatement";
}

ASTInfixExpression::ASTInfixExpression() {
    type = AT_INFIX_EXPRESSION;
    ref_count = 0;
}

ASTInfixExpression::ASTInfixExpression(Token t) {
    type = AT_INFIX_EXPRESSION;
    ref_count = 0;
    token = t;
}

ASTInfixExpression::ASTInfixExpression(Token t, ASTNode* l, ASTNode* r, std::string op) {
    type = AT_INFIX_EXPRESSION;
    ref_count = 0;
    token = t;
    left = l;
    right = r;
    _operator = op;
}

ASTInfixExpression::~ASTInfixExpression() {
    free_memory_ASTNode(left);
    free_memory_ASTNode(right);
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

ASTWhileStatement::ASTWhileStatement() {

}

ASTWhileStatement::ASTWhileStatement(Token t) {

}

std::string ASTWhileStatement::inspect() {
    return "todo: implement this";
}

std::string ASTWhileStatement::toString() {
    return "todo: implement this";
}

ASTInteger::ASTInteger() {
    type = AT_INTEGER;
    ref_count = 0;
}

ASTInteger::ASTInteger(Token t) {
    type = AT_INTEGER;
    ref_count = 0;
    token = t;
}

ASTInteger::ASTInteger(Token t, int v) {
    type = AT_INTEGER;
    ref_count = 0;
    token = t;
    value = v;
}

ASTInteger::~ASTInteger() {
    //...
}

std::string ASTInteger::toString() {
    return "ASTInteger[" + std::to_string(value) + "]";
}

std::string ASTInteger::inspect() {
    return "ASTInteger";
}

ASTPrefixExpression::ASTPrefixExpression(Token t, std::string o) {
    type = AT_PREFIX_EXPRESSION;
    ref_count = 0;
    token = t;
    _operator = o;
}

ASTPrefixExpression::~ASTPrefixExpression() {
    free_memory_ASTNode(right);
}

ASTBoolean::ASTBoolean() {
    type = AT_BOOLEAN;
    ref_count = 0;
}

ASTBoolean::ASTBoolean(Token t) {
    type = AT_BOOLEAN;
    ref_count = 0;
    token = t;
}

ASTBoolean::ASTBoolean(Token t, bool v) {
    type = AT_BOOLEAN;
    ref_count = 0;
    token = t;
    value = v;
}

ASTBoolean::~ASTBoolean() {
    //...
}

std::string ASTBoolean::toString() {
    return "ASTBoolean";
}

std::string ASTBoolean::inspect() {
    return "ASTBoolean";
}

ASTIfStatement::ASTIfStatement() {
    type = AT_IF_STATEMENT;
}

ASTIfStatement::ASTIfStatement(Token t) {
    type = AT_IF_STATEMENT;
    token = t;
}

ASTIfStatement::~ASTIfStatement() {
    free_memory_ASTNode(condition);
    free_memory_ASTNode(consequence);
    free_memory_ASTNode(alternative);
}

std::string ASTIfStatement::inspect() {
    return "todo: implement this";
}

std::string ASTIfStatement::toString() {
    return "ASTIfExpression";
}

ASTBlockStatement::ASTBlockStatement() {
    type = AT_BLOCK_STATEMENT;
}

ASTBlockStatement::ASTBlockStatement(Token t) {
    type = AT_BLOCK_STATEMENT;
    token = t;
}

ASTBlockStatement::~ASTBlockStatement() {
    for (auto& it : statements) {
        free_memory_ASTNode(it);
    }
}

std::string ASTBlockStatement::inspect() {
    return "todo: implement this";
}

std::string ASTBlockStatement::toString() {
    return "todo: implement this";
}

ASTNullExpression::ASTNullExpression() {
    type = AT_NULL_EXPRESSION;
}

std::string ASTNullExpression::inspect() {
    return "ASTNullExpression";
}

std::string ASTNullExpression::toString() {
    return "ASTNullExpression";
}

ASTLetStatement::ASTLetStatement() {
    type = AT_LET_STATEMENT;
}

ASTLetStatement::ASTLetStatement(Token t) {
    type = AT_LET_STATEMENT;
    token = t;
}

std::string ASTLetStatement::inspect() {
    return "ASTLetStatement";
}

std::string ASTLetStatement::toString() {
    return "ASTLetStatement<" + name.toString() + "> [" + value->toString() + "]\n";
}

ASTString::ASTString() {
    type = AT_STRING_LITERAL;
}

ASTString::ASTString(Token t) {
    type = AT_STRING_LITERAL;
    token = t;
}

ASTString::ASTString(Token t, std::string v) {
    type = AT_STRING_LITERAL;
    token = t;
    value = v;
}

ASTString::~ASTString() {
    //...
}

std::string ASTString::inspect() {
    return "ASTString.inspect()";
}

std::string ASTString::toString() {
    return "ASTString[" + value + "]";
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
        case AT_PROGRAM: {
            delete (ASTProgram*) node;
            break;
        }
        case AT_EXPRESSION_STATEMENT: {
            delete (ASTExpressionStatement*) node;
            break;
        }
        case AT_IDENTIFIER: {
            delete (ASTIdentifier*) node;
            break;
        }
        case AT_INTEGER: {
            delete (ASTInteger*) node;
            break;
        }
        case AT_BOOLEAN: {
            delete (ASTBoolean*) node;
            break;
        }
        case AT_INFIX_EXPRESSION: {
            delete (ASTInfixExpression*) node;
            break;
        }
        case AT_PREFIX_EXPRESSION: {
            delete (ASTPrefixExpression*) node;
            break;
        }
        case AT_LET_STATEMENT: {
            delete (ASTLetStatement*) node;
            break;
        }
        case AT_RETURN_STATEMENT: {
            delete (ASTReturnStatement*) node;
            break;
        }
        case AT_FUNCTION_STATEMENT: {
            delete (ASTFunctionStatement*) node;
            break;
        }
        case AT_DEF_STATEMENT: {
            delete (ASTDefStatement*) node;
            break;
        }
        case AT_WHILE_STATEMENT: {
            delete (ASTWhileStatement*) node;
            break;
        }
        case AT_FOR_STATEMENT: {
            delete (ASTForStatement*) node;
            break;
        }
        case AT_IF_STATEMENT: {
            delete (ASTIfStatement*) node;
            break;
        }
        case AT_BLOCK_STATEMENT: {
            delete (ASTBlockStatement*) node;
            break;
        }
        case AT_NULL_EXPRESSION: {
            delete (ASTNullExpression*) node;
            break;
        }
        case AT_STRING_LITERAL: {
            delete (ASTString*) node;
            break;
        }
        default: {
            std::cout << "SEVERE MEMORY ERROR!!!\n";
            break;
        }
    }
}