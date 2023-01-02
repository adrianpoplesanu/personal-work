#include "ast.h"

#include <iostream>

void print_AST_node(ASTNode* node, int level) {
    for (int i = 0; i < level; i++) {
        std::cout << " ";
    }
    switch(node->type) {
        case AST_PROGRAM: {
            ASTProgram *program = (ASTProgram*) node;
            std::cout << "-> ASTProgram\n";
            for (int i = 0; i < program->statements.size(); i++) {
                print_AST_node(program->statements.at(i), level + 2);
            }
        break;
        }
        case AST_EXPRESSION_STATEMENT: {
            ASTExpressionStatement *expressionStatement = (ASTExpressionStatement*) node;
            std::cout << "-> ASTExpressionStatement\n";
            print_AST_node(expressionStatement->expression, level + 2);
        break;
        }
        case AST_INFIX_EXPRESSION: {
            ASTInfixExpression *infixExpression = (ASTInfixExpression*) node;
            std::cout << "-> InfixExpression [" + infixExpression->_operator + "]\n";
            print_AST_node(infixExpression->left, level + 2);
            print_AST_node(infixExpression->right, level + 2);
        break;
        }
        case AST_INTEGER: {
            ASTInteger *integer = (ASTInteger*) node;
            std::cout << "-> Integer [" << integer->value << "]\n";
        break;
        }
        default: {
            std::cout << "UNKNOWN AST NODE\n";
        break;
        }
    }
}