#ifndef __COMPILATION_SCOPE_H
#define __COMPILATION_SCOPE_H

#include "instructions.h"
#include "emitted_instruction.h"

class CompilationScope {
public:
    CompilationScope();
    CompilationScope(Instructions);
    CompilationScope(Instructions, EmittedInstruction, EmittedInstruction);
    Instructions instructions; // TODO: check if this is correct
    EmittedInstruction previousInstruction = EmittedInstruction();
    EmittedInstruction lastInstruction = EmittedInstruction();
};

#endif