#ifndef __VM_H
#define __VM_H

#include "objects.h"
#include "bytecode.h"
#include "code.h"
#include "gc.h"
#include "settings.h"
#include <vector>

class VM {
public:
    Code code;

    int stackSize = 2048;
    int sp; // stack pointer
    Instructions instructions;
    std::vector<AdObject*> constants;
    AdObject *stack[2048];
    AdObject *globals[65536];
    GarbageCollector *gc;

    VM();
    void load(Bytecode);
    void setGarbageCollector(GarbageCollector*);
    AdObject* stackTop();
    void run();
    AdObject* last_popped_stack_element();
    AdObject* last_popped_stack_elem();
    void printStack();
    void push(AdObject *);
    AdObject* pop();
    AdObject* nativeBooleanToBooleanObject(bool);
    bool isTruthy(AdObject*);

    void executeBinaryOperations(unsigned char);
    void executeBinaryIntegerOperations(unsigned char, AdObject*, AdObject*);
    void executeBinaryStringOperations(unsigned char, AdObject*, AdObject*);
    AdObject* buildArray(int, int);
    AdObject* buildHash(int, int);
};

#endif