#ifndef __COMPILER_H
#define __COMPILER_H

#include "ast.h"
#include "bytecode.h"
#include "code.h"
#include "opcode.h"

class Compiler {
public:
    Instructions instructions;
    Bytecode bytecode;
    Code code;
    std::vector<AdObject*> constants;

    Compiler();
    void reset();
    void compile(ASTNode*);
    int emit(OpCode, int, std::list<int>&);
    int addInstruction(unsigned char *);
    int addConstant(AdObject*);
    Bytecode getBytecode();
};

#endif