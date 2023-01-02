#ifndef __PROGRAM_H
#define __PROGRAM_H

#include "lexer.h"
#include "evaluator.h"
#include "parser.h"
#include "ast.h"

class Program {
public:
    Evaluator evaluator;
    Parser parser;
    Environment *env;

    Program();

    void loop();
};

#endif
