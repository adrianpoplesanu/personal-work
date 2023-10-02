#ifndef __COMPILER_H
#define __COMPILER_H

#include "ast.h"
#include "bytecode.h"
#include "code.h"
#include "opcode.h"
#include "gc.h"

class Compiler {
public:
    Instructions instructions;
    Bytecode bytecode;
    Code code;
    std::vector<AdObject*> constants;
    GarbageCollector *gc;

    Compiler();
    void reset();
    void compile(ASTNode*);
    int emit(OpCode, int, std::vector<int>&);
    int addInstruction(int, unsigned char *);
    int addConstant(AdObject*);
    Bytecode getBytecode();
};

#endif