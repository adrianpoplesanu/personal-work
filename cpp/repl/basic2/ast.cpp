#include "ast.h"

ASTProgram::ASTProgram() {
    type = AST_PROGRAM;
    ref_count = 0;
}

ASTExpressionStatement::ASTExpressionStatement(Token t) {
    type = AST_EXPRESSION_STATEMENT;
    token = t;
    ref_count = 0;
}

ASTInteger::ASTInteger(Token t) {
    type = AST_INTEGER;
    token = t;
    ref_count = 0;
}

ASTInfixExpression::ASTInfixExpression(Token t) {
    type = AST_INFIX_EXPRESSION;
    token = t;
    ref_count = 0;
}