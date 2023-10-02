#ifndef __VM_H
#define __VM_H

#include "objects.h"
#include "bytecode.h"

class VM {
public:
    int stackSize = 2048;
    int sp; // stack pointer
    Instructions instructions;
    AdObject stack[2048];

    VM();
    void load(Bytecode);
    void run();
    AdObject* last_popped_stack_element();
};

#endif