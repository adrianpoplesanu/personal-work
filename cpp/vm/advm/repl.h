#ifndef __REPL_H
#define __REPL_H

#include "parser.h"
#include "compiler.h"
#include "vm.h"
#include "gc.h"

class Repl {
    public:
    Parser parser;
    ASTProgram *program;
    Compiler compiler;
    VM vm;
    GarbageCollector *gc;

    Repl();
    ~Repl();
    void loop();
    void executeFile(std::ifstream &);
};

#endif