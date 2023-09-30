#ifndef __REPL_H
#define __REPL_H

#include "parser.h"
#include "compiler.h"
#include "vm.h"

class Repl {
    public:
    Parser parser;
    ASTProgram program;
    Compiler compiler;
    VM vm;

    void loop();
};

#endif