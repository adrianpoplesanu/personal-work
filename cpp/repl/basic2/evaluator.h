#ifndef __EVALUATOR_H
#define __EVALUATOR_H

#include "environment.h"
#include "objects.h"
#include "ast.h"

class Evaluator {
public:
    Evaluator();
    Object* eval(ASTNode*, Environment*);
    Object* evalProgam(ASTNode*, Environment*);
    Object* evalExpressionStatement(ASTNode*, Environment*);
    Object* evalInfixExpression(ASTNode*, Environment*);
    Object* evalInteger(ASTNode*, Environment*);
};

#endif
