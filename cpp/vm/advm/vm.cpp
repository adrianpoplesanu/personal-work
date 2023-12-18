#include "vm.h"

VM::VM() {
    sp = 0;
}

void VM::load(Bytecode b) {
    instructions = b.instructions;
    constants = b.constants;
    for (int i = 0; i < 2048; i++) {
        if (i < sp) { // TODO: this works but looks bad, i need something more elegant here
            AdObject* prev = stack[i]->prev;
            AdObject* next = stack[i]->next;

            if (prev) {
                prev->next = next;
            }
            if (next) {
                next->prev = prev;
            }

            delete stack[i];
        }
        stack[i] = NULL;
    }
}

AdObject* VM::stackTop() {
    if (sp == 0) return NULL;
    return stack[sp - 1];
}

void VM::run(GarbageCollector *gc) {
    for (int ip = 0; ip < instructions.bytes.size(); ip++) {
        unsigned char opcode = instructions.bytes[ip];
        switch (opcode) {
            case 0: {
                // 0 e OpConstant
                int constIndex = readUint16(instructions, ip + 1);
                ip += 2;
                push(constants.at(constIndex));
                break;
            }
            case 1: {
                // 1 e OpAdd
                AdObject *right = pop();
                AdObject *left = pop();

                int leftValue = ((AdObjectInteger*) left)->value;
                int rightValue = ((AdObjectInteger*) right)->value;

                int result = leftValue + rightValue;
                AdObject* obj = new AdObjectInteger(result);
                gc->addObject(obj);
                push(obj);
                break;
            }
            case 2: {
                // 2 e OpMinus
                AdObject *right = pop();
                AdObject *left = pop();

                int leftValue = ((AdObjectInteger*) left)->value;
                int rightValue = ((AdObjectInteger*) right)->value;

                int result = leftValue - rightValue;
                push(new AdObjectInteger(result));
                break;
            }
            case 3: {
                // 3 e OpMultiply
                AdObject *right = pop();
                AdObject *left = pop();

                int leftValue = ((AdObjectInteger*) left)->value;
                int rightValue = ((AdObjectInteger*) right)->value;

                int result = leftValue * rightValue;
                push(new AdObjectInteger(result));
                break;
            }
            case 4: {
                // 4 e OpDivide
                AdObject *right = pop();
                AdObject *left = pop();

                int leftValue = ((AdObjectInteger*) left)->value;
                int rightValue = ((AdObjectInteger*) right)->value;

                int result = leftValue / rightValue;
                push(new AdObjectInteger(result));
                break;
            }
            default: {
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