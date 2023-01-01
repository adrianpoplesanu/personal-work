#ifndef __PROGRAM_H
#define __PROGRAM_H

#include "lexer.h"
#include "evaluator.h"
#include "parser.h"

class Program {
public:
    Evaluator evaluator;
    Parser parser;

    Program();

    void loop();
};

#endif
