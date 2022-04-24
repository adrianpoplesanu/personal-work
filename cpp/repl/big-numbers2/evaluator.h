#ifndef __EVALUATOR_H
#define __EVALUATOR_H

#include "objects.h"
#include "ast.h"
#include "environment.h"

class Evaluator {
    public:
        BNObject* eval(AstNode*, Environment&);
        BNObject* evalBigNumber(AstNode*, Environment&);
        BNObject* evalProgram(AstNode*, Environment&);
        BNObject* evalIdentifier(AstNode*, Environment&);
        BNObject* evalAssignStatement(AstNode*, Environment&);
};

#endif