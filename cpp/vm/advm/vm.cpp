#include "vm.h"

VM::VM() {
    sp = 0;
}

void VM::load(Bytecode b) {
    instructions = b.instructions;
    constants = b.constants;
    for (int i = 0; i < 2048; i++) {
        if (i < sp) { // TODO: this works but looks bad
            delete stack[i];
        }
        stack[i] = NULL;
    }
}

AdObject* VM::stackTop() {
    if (sp == 0) return NULL;
    return stack[sp - 1];
}

void VM::run() {
    // ...
}

AdObject* VM::last_popped_stack_element() {
    return NULL;
}

void VM::push(AdObject* obj) {
    if (sp >= stackSize) {
        std::cout << "ERROR: stack overflow";
    } else {
        stack[sp++] = obj;
    }
}

AdObject* VM::pop() {
    AdObject* result = stack[sp - 1];
    sp--;
    return result;
}