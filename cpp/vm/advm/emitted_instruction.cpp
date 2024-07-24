#include "emitted_instruction.h"

EmittedInstruction::EmittedInstruction() {
    opcode = OpCode(); // this is a bit ugly
    position = 0;
}

EmittedInstruction::EmittedInstruction(OpCode o, int p) {
    opcode = o;
    position = p;
}