#include "vm.h"

AdObjectNull NULLOBJECT;
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
            case OP_ADD:
            case OP_SUB:
            case OP_MULTIPLY:
            case OP_DIVIDE: {
                executeBinaryOperations(opcode);
                break;
            }
            /*case OP_ADD: {
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
            }*/
            case OP_POP: {
                // 5 e OpPop
                if (PRINT_LAST_ELEMENT_ON_STACK) {
                    if (sp == 1) {
                        AdObject *res = pop();
                        std::cout << res->inspect() << "\n";
                    }
                } else {
                    pop();
                }
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
                if (obj->type == OT_BOOL) {
                    AdObjectBoolean* operand = (AdObjectBoolean*) obj;
                    if (operand->value == TRUE.value) {
                        push(nativeBooleanToBooleanObject(false));
                    } else if (operand->value == FALSE.value) {
                        push(nativeBooleanToBooleanObject(true));
                    } else {
                        push(nativeBooleanToBooleanObject(false));
                    }
                }
                if (obj->type == OT_NULL) {
                    push(nativeBooleanToBooleanObject(true));
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
            case OP_JUMP: {
                int pos = readUint16(instructions, ip + 1);
                ip = pos - 1;
                break;
            }
            case OP_JUMP_NOT_TRUTHY: {
                int pos = readUint16(instructions, ip + 1);
                ip += 2;

                AdObject *condition = pop();
                if (!isTruthy(condition)) {
                    ip = pos - 1;
                }

                break;
            }
            case OP_NULL: {
                push(&NULLOBJECT);
                break;
            }
            case OP_SET_GLOBAL: {
                int globalIndex = readUint16(instructions, ip + 1);
                ip += 2;
                globals[globalIndex] = pop();
                break;
            }
            case OP_GET_GLOBAL: {
                int globalIndex = readUint16(instructions, ip + 1);
                ip += 2;
                push(globals[globalIndex]);
                break;
            }
            case OP_ARRAY: {
                int numElements = readUint16(instructions, ip + 1);
                ip += 2;

                AdObject *arrayObj = buildArray(sp - numElements, sp);
                sp = sp - numElements;

                push(arrayObj);

                break;
            }
            case OP_HASH: {
                int numElements = readUint16(instructions, ip + 1);
                ip += 2;

                AdObject *hashObj = buildHash(sp - numElements, sp);
                sp = sp - numElements;

                push(hashObj);
                break;
            }
            case OP_INDEX_EXPRESSION: {
                AdObject *index = pop();
                AdObject *left = pop();
                executeIndexExpression(left, index);
                break;
            }
            case OP_CALL: {
                std::cout << "todo: handle OP_CALL in vm.run()\n";
                break;
            }
            case OP_RETURN_VALUE: {
                std::cout << "todo: handle OP_RETURN_VALUE in vm.run()\n";
                break;
            }
            case OP_RETURN: {
                std::cout << "todo: handle OP_RETURN in vm.run()\n";
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
        std::cout << "stack error: index out of bounds\n";
    } else {
        stack[sp++] = obj;
    }
}

AdObject* VM::pop() {
    if (sp - 1 < 0) {
        std::cout << "stack error: index out of bounds\n";
        return NULL;
    }
    AdObject* result = stack[sp - 1];
    sp--;
    return result;
}

AdObject* VM::buildArray(int start, int end) {
    std::vector<AdObject*> elements;
    for (int i = start; i < end; ++i) {
        elements.push_back(stack[i]);
    }
    AdObjectList *obj = new AdObjectList(elements);
    gc->addObject(obj);
    return obj;
}

AdObject* VM::buildHash(int start, int end) {
    std::unordered_map<std::string, HashPair> hashedPairs;

    for (int i = start; i < end; i+=2) {
        AdObject *key = stack[i];
        AdObject *value = stack[i + 1];

        std::hash<std::string> hash_string;
        HashPair hash_pair(key, value);
        hashedPairs.insert(std::make_pair(std::to_string(hash_string(key->hash())), hash_pair)); // value needs to be a HashPair
    }

    AdObjectHash *obj = new AdObjectHash(hashedPairs);
    gc->addObject(obj);
    return obj;
}

AdObject* VM::nativeBooleanToBooleanObject(bool value) {
    if (value) {
        return &TRUE;
    }
    return &FALSE;
}

bool VM::isTruthy(AdObject* obj) {
    if (obj->type == OT_BOOL) {
        return ((AdObjectBoolean*) obj)->value;
    }
    if (obj->type == OT_NULL) {
        return false;
    }
    return true;
}

void VM::executeBinaryOperations(unsigned char opcode) {
    AdObject *right = pop();
    AdObject *left = pop();

    ObjectType right_type = right->type;
    ObjectType left_type = left->type;

    if (right_type == OT_INT && left_type == OT_INT) {
        executeBinaryIntegerOperations(opcode, right, left);
    }
    if (right_type == OT_STRING && left_type == OT_STRING) {
        executeBinaryStringOperations(opcode, right, left);
    }
}

void VM::executeBinaryIntegerOperations(unsigned char opcode, AdObject *right, AdObject *left) {
    int resultValue;
    int rightValue = ((AdObjectInteger*) right)->value;
    int leftValue = ((AdObjectInteger*) left)->value;
    switch(opcode) {
        case OP_ADD:
            resultValue = leftValue + rightValue;
            break;
        case OP_SUB:
            resultValue = leftValue - rightValue;
            break;
        case OP_MULTIPLY:
            resultValue = leftValue * rightValue;
            break;
        case OP_DIVIDE:
            resultValue = leftValue / rightValue;
            break;
    }
    AdObjectInteger *result = new AdObjectInteger(resultValue);
    gc->addObject(result);
    push(result);
}

void VM::executeBinaryStringOperations(unsigned char opcode, AdObject *right, AdObject *left) {
    std::string resultValue = "";
    std::string rightValue = ((AdObjectString*) right)->value;
    std::string leftValue = ((AdObjectString*) left)->value;
    switch(opcode) {
        case OP_ADD:
            resultValue = leftValue + rightValue;
            break;
    }
    AdObjectString *result = new AdObjectString(resultValue);
    push(result);
}

void VM::executeIndexExpression(AdObject *left, AdObject *index) {
    if (left->type == OT_LIST) {
        executeArrayIndex(left, index);
    }
    if (left->type == OT_HASH) {
        executeHashIndex(left, index);
    }
}

void VM::executeArrayIndex(AdObject *left, AdObject *index) {
    int i = ((AdObjectInteger*) index)->value;
    int max = ((AdObjectList*) left)->elements.size();
    if (i < 0 || i >= max) {
        push(&NULLOBJECT);
    } else {
        push(((AdObjectList*) left)->elements.at(i));
    }
}

void VM::executeHashIndex(AdObject *left, AdObject *index) {
    AdObjectHash *hashObject = (AdObjectHash*) left;
    std::hash<std::string> hash_string;
    AdObject *result = hashObject->pairs[std::to_string(hash_string(index->hash()))].value;
    if (result) {
        push(result);
    } else {
        push(&NULLOBJECT);
    }
}