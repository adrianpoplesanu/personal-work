#ifndef __COMPILATION_SCOPE_H
#define __COMPILATION_SCOPE_H

#include "instructions.h"
#include "emitted_instruction.h"

class CompilationScope {
public:
    CompilationScope();
    Instructions instructions; // TODO: check if this is correct
    EmittedInstruction previousInstruction = EmittedInstruction();
    EmittedInstruction lastInstruction = EmittedInstruction();
};

#endif