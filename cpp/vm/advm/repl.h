#ifndef __REPL_H
#define __REPL_H

#include "parser.h"

class Repl {
    public:
    Parser parser;
    ASTProgram program;

    void loop();
};

#endif