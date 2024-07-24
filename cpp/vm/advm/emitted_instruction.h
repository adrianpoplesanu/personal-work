#ifndef __EMITTED_INSTRUCTION_H
#define __EMITTED_INSTRUCTION_H

#include "opcode.h"

class EmittedInstruction {
public:
    EmittedInstruction();
    EmittedInstruction(OpCode, int);

    OpCode opcode;
    int position;
};

#endif