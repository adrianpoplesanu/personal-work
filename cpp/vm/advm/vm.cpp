#include "vm.h"

VM::VM() {
    sp = 0;
}

void VM::load(Bytecode b) {
    instructions = b.instructions;
}

void VM::run() {
    // ...
}

AdObject* VM::last_popped_stack_element() {
    return NULL;
}