#ifndef __EVALUATOR_H
#define __EVALUATOR_H

#include "environment.h"
#include "ast.h"
#include "objects.h"

class Evaluator {
    public:
    AdObject* eval(ASTNode* node, Environment* env);
};

#endif