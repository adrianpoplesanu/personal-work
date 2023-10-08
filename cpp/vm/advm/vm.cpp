#include "vm.h"

VM::VM() {
    sp = 0;
}

void VM::load(Bytecode b) {
    instructions = b.instructions;
}

AdObject* VM::stackTop() {
    return NULL;
}

void VM::run() {
    // ...
}

AdObject* VM::last_popped_stack_element() {
    return NULL;
}

void VM::push(AdObject* obj) {

}

AdObject* VM::pop() {
    return NULL;
}