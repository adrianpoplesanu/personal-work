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
    for (int ip = 0; ip < instructions.bytes.size(); ip++) {
        unsigned char opcode = instructions.bytes[ip];
        switch (opcode) {
            case 0: {
                // 0 e OpConstant
                //std::cout << "aaa\n";
                int constIndex = readUint16(instructions, ip + 1);
                ip += 2;
                push(constants.at(constIndex));
                break;
            }
            case 1: {
                // 1 e OpAdd
                //std::cout << "bbb\n";
                AdObject *right = pop();
                AdObject *left = pop();

                int leftValue = ((AdObjectInteger*) left)->value;
                //std::cout << leftValue << "\n";
                int rightValue = ((AdObjectInteger*) right)->value;
                //std::cout << rightValue << "\n";

                int result = leftValue + rightValue;
                push(new AdObjectInteger(result));
                break;
            }
            default: {
                //std::cout << "ccc\n";
                break;
            }
        }
    }
}

AdObject* VM::last_popped_stack_element() {
    if (sp == 0) {
        return NULL;
    }
    return stack[sp - 1];
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