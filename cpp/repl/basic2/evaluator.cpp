#include "evaluator.h"
#include "ast.h"

#include <iostream>

Evaluator::Evaluator() {

}

Object* Evaluator::eval(ASTNode *node, Environment *env) {
    switch(node->type) {
        case AST_PROGRAM: {
            return evalProgam(node, env);
            break;
        }
        case AST_EXPRESSION_STATEMENT: {
            return evalExpressionStatement(node, env);
            break;
        }
        case AST_INFIX_EXPRESSION: {
            return evalInfixExpression(node, env);
            break;
        }
        case AST_INTEGER: {
            return evalInteger(node, env);
            break;
        }
        default: {
            std::cout << "UNKNOWN EVALUATION OF AST NODE\n";
            break;
        }
    }
    return NULL;
}

Object* Evaluator::evalProgam(ASTNode *node, Environment *env) {
    ASTProgram *program = (ASTProgram*) node;
    for (int i = 0; i < program->statements.size(); i++) {
        Object *result = eval(program->statements.at(i), env);
        std::cout << result->inspect() << "\n";
    }
    return NULL;
}

Object* Evaluator::evalExpressionStatement(ASTNode *node, Environment *env) {
    ASTExpressionStatement *expressionStatement = (ASTExpressionStatement*) node;
    return eval(expressionStatement->expression, env);
}

Object* Evaluator::evalInfixExpression(ASTNode *node, Environment *env) {
    ASTInfixExpression *infixExpression = (ASTInfixExpression*) node;
    Object *left = eval(infixExpression->left, env);
    Object *right = eval(infixExpression->right, env);
    Object *result = NULL;
    if (left->type == INTEGER && right->type == INTEGER) {
        if (infixExpression->_operator == "+") {
            result = new IntegerObject();
            ((IntegerObject*) result)->value = ((IntegerObject*) left)->value + ((IntegerObject*) right)->value;
        }
        else if (infixExpression->_operator == "-") {
            result = new IntegerObject();
            ((IntegerObject*) result)->value = ((IntegerObject*) left)->value - ((IntegerObject*) right)->value;
        }
        else if (infixExpression->_operator == "*") {
            result = new IntegerObject();
            ((IntegerObject*) result)->value = ((IntegerObject*) left)->value * ((IntegerObject*) right)->value;
        }
        else if (infixExpression->_operator == "/") {
            result = new IntegerObject();
            ((IntegerObject*) result)->value = ((IntegerObject*) left)->value / ((IntegerObject*) right)->value;
        }
        else {
            std::cout << "UNKNOWN OPERATOR FOR INTEGER INFIX EXPRESSION";
        }
    }
    return result;
}

Object* Evaluator::evalInteger(ASTNode *node, Environment *env) {
    IntegerObject *obj = new IntegerObject();
    obj->value = ((ASTInteger*) node)->value;
    return obj;
}