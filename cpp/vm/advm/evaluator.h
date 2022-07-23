#ifndef __EVALUATOR_H
#define __EVALUATOR_H

#include "environment.h"
#include "ast.h"
#include "objects.h"

class Evaluator {
    public:
    std::vector<Environment*> environment_gc_list;

    AdObject* eval(ASTNode* node, Environment* env);

    void initEnvironmentGarbageCollection();
    void garbageCollectEnvironments();
};

#endif