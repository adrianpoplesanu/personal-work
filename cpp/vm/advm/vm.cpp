#include "vm.h"

AdObjectBoolean TRUE(true, true);
AdObjectBoolean FALSE(false, true);

VM::VM() {
    sp = 0;
}

void VM::load(Bytecode b) {
    instructions = b.instructions;
    constants = b.constants;
    for (int i = 0; i < 2048; i++) {
        stack[i] = NULL;
    }
}

void VM::setGarbageCollector(GarbageCollector *gc) {
    this->gc = gc;
}

AdObject* VM::stackTop() {
    if (sp == 0) return NULL;
    return stack[sp - 1];
}

void VM::run() {
    for (int ip = 0; ip < instructions.bytes.size(); ip++) {
        unsigned char opcode = instructions.bytes[ip];
        switch (opcode) {
            case OP_CONSTANT: {
                // 0 e OpConstant
                int constIndex = readUint16(instructions, ip + 1);
                ip += 2;
                push(constants.at(constIndex));
                break;
            }
            case OP_ADD: {
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
            case OP_SUB: {
                // 2 e OpMinus
                AdObject *right = pop();
                AdObject *left = pop();

                int leftValue = ((AdObjectInteger*) left)->value;
                int rightValue = ((AdObjectInteger*) right)->value;

                int result = leftValue - rightValue;
                AdObject* obj = new AdObjectInteger(result);
                gc->addObject(obj);
                push(obj);
                break;
            }
            case OP_MULTIPLY: {
                // 3 e OpMultiply
                AdObject *right = pop();
                AdObject *left = pop();

                int leftValue = ((AdObjectInteger*) left)->value;
                int rightValue = ((AdObjectInteger*) right)->value;

                int result = leftValue * rightValue;
                AdObject* obj = new AdObjectInteger(result);
                gc->addObject(obj);
                push(obj);
                break;
            }
            case OP_DIVIDE: {
                // 4 e OpDivide
                AdObject *right = pop();
                AdObject *left = pop();

                int leftValue = ((AdObjectInteger*) left)->value;
                int rightValue = ((AdObjectInteger*) right)->value;

                int result = leftValue / rightValue;
                AdObject* obj = new AdObjectInteger(result);
                gc->addObject(obj);
                push(obj);
                break;
            }
            case OP_POP: {
                // 5 e OpPop
                pop();
                break;
            }
            case OP_TRUE: {
                // 6 e OpTrue
                push(nativeBooleanToBooleanObject(true));
                break;
            }
            case OP_FALSE: {
                // 7 e OpFalse
                push(nativeBooleanToBooleanObject(false));
                break;
            }
            case OP_GREATERTHAN: {
                AdObject *right = pop();
                AdObject *left = pop();

                int leftValue = ((AdObjectInteger*) left)->value;
                int rightValue = ((AdObjectInteger*) right)->value;

                push(nativeBooleanToBooleanObject(leftValue > rightValue));
                break;
            }
            case OP_GREATERTHANEQUAL: {
                AdObject *right = pop();
                AdObject *left = pop();

                int leftValue = ((AdObjectInteger*) left)->value;
                int rightValue = ((AdObjectInteger*) right)->value;

                push(nativeBooleanToBooleanObject(leftValue >= rightValue));
                break;
            }
            case OP_EQUALS: {
                AdObject *right = pop();
                AdObject *left = pop();

                int leftValue = ((AdObjectInteger*) left)->value;
                int rightValue = ((AdObjectInteger*) right)->value;

                push(nativeBooleanToBooleanObject(leftValue == rightValue));
                break;
            }
            case OP_BANG: {
                AdObject *obj = pop();
                AdObjectBoolean* operand = (AdObjectBoolean*) obj;
                if (operand->value == TRUE.value) {
                    push(nativeBooleanToBooleanObject(false));
                } else if (operand->value == FALSE.value) {
                    push(nativeBooleanToBooleanObject(true));
                } else {
                    push(nativeBooleanToBooleanObject(false));
                }
                break;
            }
            case OP_MINUS: {
                AdObject *operand = pop();
                if (operand->type != OT_INT) {
                    std::cout << "unsupported type negation\n";
                }
                int value = ((AdObjectInteger*) operand)->value;
                AdObject *obj = new AdObjectInteger(-value);
                gc->addObject(obj);
                push(obj);
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

AdObject* VM::last_popped_stack_elem() {
    return stack[sp];
}

void VM::printStack() {
    int i = 0;
    std::cout << "[";
    while (i < sp) {
        std::cout << stack[i]->inspect();
        i++;
        if (i < sp) {
            std::cout << ", ";
        }
    }
    std::cout << "]\n";
}

void VM::push(AdObject* obj) {
    if (sp >= stackSize) {
        std::cout << "ERROR: stack overflow";
    } else {
        stack[sp++] = obj;
    }
}

AdObject* VM::pop() {
    if (sp - 1 < 0) {
        std::cout << "error: stack underflow\n";
        return NULL;
    }
    AdObject* result = stack[sp - 1];
    sp--;
    return result;
}

AdObject* VM::nativeBooleanToBooleanObject(bool value) {
    if (value) {
        return &TRUE;
    }
    return &FALSE;
}
