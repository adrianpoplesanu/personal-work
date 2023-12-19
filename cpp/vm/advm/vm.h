#ifndef __VM_H
#define __VM_H

#include "objects.h"
#include "bytecode.h"
#include "code.h"
#include "gc.h"
#include <vector>

class VM {
public:
    Code code;

    int stackSize = 2048;
    int sp; // stack pointer
    Instructions instructions;
    std::vector<AdObject*> constants; // TODO: this will leak memory
    AdObject *stack[2048];
    GarbageCollector *gc;

    VM();
    void load(Bytecode);
    void setGarbageCollector(GarbageCollector*);
    AdObject* stackTop();
    void run(GarbageCollector*);
    AdObject* last_popped_stack_element();
    void push(AdObject*);
    AdObject* pop();
};

#endif