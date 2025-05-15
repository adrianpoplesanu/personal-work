#include "code.h"
#include <cstring>
#include <sstream>

Code::Code() {
    definitionsMap.insert(std::make_pair(OP_CONSTANT, new Definition("OpConstant", 1, new int[1] {2})));
    definitionsMap.insert(std::make_pair(OP_ADD, new Definition("OpAdd", 0, new int)));
    definitionsMap.insert(std::make_pair(OP_SUB, new Definition("OpSub", 0, new int)));
    definitionsMap.insert(std::make_pair(OP_MULTIPLY, new Definition("OpMultiply", 0, new int)));
    definitionsMap.insert(std::make_pair(OP_DIVIDE, new Definition("OpDivide", 0, new int)));
    definitionsMap.insert(std::make_pair(OP_POP, new Definition("OpPop", 0, new int)));
    definitionsMap.insert(std::make_pair(OP_TRUE, new Definition("OpTrue", 0, new int)));
    definitionsMap.insert(std::make_pair(OP_FALSE, new Definition("OpFalse", 0, new int)));
    definitionsMap.insert(std::make_pair(OP_GREATERTHAN, new Definition("OpGreaterThan", 0, new int)));
    definitionsMap.insert(std::make_pair(OP_EQUALS, new Definition("OpEquals", 0, new int)));
    definitionsMap.insert(std::make_pair(OP_GREATERTHANEQUAL, new Definition("OpGreaterThanEqual", 0, new int)));
    definitionsMap.insert(std::make_pair(OP_MINUS, new Definition("OpMinus", 0, new int)));
    definitionsMap.insert(std::make_pair(OP_BANG, new Definition("OpBang", 0, new int)));
    definitionsMap.insert(std::make_pair(OP_JUMP_NOT_TRUTHY, new Definition("OpJumpNotTruthy", 1, new int[1] {2})));
    definitionsMap.insert(std::make_pair(OP_JUMP, new Definition("OpJump", 1, new int[1] {2})));
    definitionsMap.insert(std::make_pair(OP_NULL, new Definition("OpNull", 0, new int)));
    definitionsMap.insert(std::make_pair(OP_GET_GLOBAL, new Definition("OpGetGlobal", 1, new int[1] {2})));
    definitionsMap.insert(std::make_pair(OP_SET_GLOBAL, new Definition("OpSetGlobal", 1, new int[1] {2})));
    definitionsMap.insert(std::make_pair(OP_ARRAY, new Definition("OpArray", 1, new int[1] {2})));
    definitionsMap.insert(std::make_pair(OP_HASH, new Definition("OpHash", 1, new int[1] {2})));
    definitionsMap.insert(std::make_pair(OP_INDEX_EXPRESSION, new Definition("OpIndexExpression", 0, new int)));
    definitionsMap.insert(std::make_pair(OP_CALL, new Definition("OpCall", 1, new int[1] {1})));
    definitionsMap.insert(std::make_pair(OP_RETURN_VALUE, new Definition("OpReturnValue", 0, new int)));
    definitionsMap.insert(std::make_pair(OP_RETURN, new Definition("OpReturn", 0, new int)));
    definitionsMap.insert(std::make_pair(OP_GET_LOCAL, new Definition("OpGetLocal", 1, new int[1] {1})));
    definitionsMap.insert(std::make_pair(OP_SET_LOCAL, new Definition("OpSetLocal", 1, new int[1] {1})));
    definitionsMap.insert(std::make_pair(OP_GET_BUILTIN, new Definition("OpGetBuiltin", 1, new int[1] {1})));
    definitionsMap.insert(std::make_pair(OP_CLOSURE, new Definition("OpClosure", 2, new int[2] {2, 1})));
    definitionsMap.insert(std::make_pair(OP_GET_FREE, new Definition("OpGetFree", 1, new int[1] {1})));
    definitionsMap.insert(std::make_pair(OP_CURRENT_CLOSURE, new Definition("OpCurrentClosure", 0, new int)));
    definitionsMap.insert(std::make_pair(OP_CLASS, new Definition("OpClass", 0, new int)));
}

Code::~Code() {
    for(std::map<unsigned char, Definition*>::iterator it = definitionsMap.begin(); it != definitionsMap.end(); it++) {
        delete it->second;
    }
}

unsigned char* Code::make(OpCode opCode, int n, std::vector<int> &args, int &size) { // TODO: rename args to operands, it's what it is
    Definition *definition = lookup(opCode.byteCode);

    int instructionLen = 1;

    for (int i = 0; i < definition->size; i++) {
        instructionLen += definition->operandWidths[i];
    }

    unsigned char *instruction = new unsigned char[instructionLen];
    instruction[0] = (unsigned char)opCode.byteCode;
    //std::cout << (int) instruction[0];

    int offset = 1;
    int i = 0;
    for(int j = 0; j < n; j++) {
        int width = definition->operandWidths[i++];
        switch(width) {
            case 2: {
                int argument = args.at(j);
                instruction[offset] = intToBytes(argument)[2];
                instruction[offset + 1] = intToBytes(argument)[3];
                break;
            }
            case 1: {
                int argument = args.at(j);
                instruction[offset] = (unsigned char)intToBytes(argument)[3]; // am pus intToBytes[0] sau poate trebui [1], nu fii atent, trebuie sa fie [3]
                break;
            }
            default: {
                std::cout << "severe error: unknown width " << width << "\n";
                break;
            }
        }
        offset += width;
    }
    size = instructionLen;
    return instruction;
}

Definition* Code::lookup(unsigned char op) {
    if (definitionsMap.find(op) == definitionsMap.end()) {
        std::cout << "definition lookup error for op=" << op << "\n";
    }
    return definitionsMap[op];
}

std::string Code::toString() {
    std::string out = "";
    int i = 0;
    while (i < instructions.size) {
        Definition* definition = lookup(instructions.bytes.at(i));
        std::vector<int> operands;
        int read;
        readOperands(definition, instructions, i + 1, operands, read);
        //out += String.format("%04d %s\n", i, formatInstruction(definition, operands));
        out += formatInt(i) + " " + formatInstruction(definition, operands) + "\n";
        i += 1 + read;
    }
    return out;
}

std::vector<unsigned char> intToBytes(int paramInt) {
    std::vector<unsigned char> arrayOfByte(4);
    for (int i = 0; i < 4; i++)
        arrayOfByte[3 - i] = (paramInt >> (i * 8));
    return arrayOfByte;
}

void readOperands(Definition *definition, Instructions instructions, int start, std::vector<int>& operands, int& read) {
    int offset = 0;

    int i = 0;
    for (int w = 0; w < definition->size; w++) {
        switch (definition->operandWidths[w]) {
            case 2: {
                operands.push_back(readUint16(instructions, start + offset));
                break;
            }
            case 1: {
                operands.push_back(readUint8(instructions, start + offset));
                break;
            }
        }
        offset += definition->operandWidths[w];
    }
    read = offset;
}

int readUint16(Instructions instructions, int offset) {
    //unsigned char bytes[4]{ 0, 0, instructions.bytes[offset], instructions.bytes[offset + 1] };
    unsigned char bytes[4]{ instructions.bytes[offset + 1], instructions.bytes[offset], 0, 0 }; // TODO: verify this is ok, run more tests!!!
    //unsigned char bytes[4]{ 255, 255, 0, 0 }; // 65535

    int value;
    std::memcpy(&value, bytes, sizeof(int));
    return value;
}

int readUint8(Instructions instructions, int offset) {
    unsigned char bytes[2]{ instructions.bytes[offset], 0 };

    int value;
    std::memcpy(&value, bytes, sizeof(short));
    return value;
}

std::string formatInt(int num) {
  std::ostringstream oss;
  oss << std::setfill('0') << std::setw(4) << num;
  return oss.str();
};

std::string formatInstruction(Definition* definition, std::vector<int> operands) {
    int operandCount = definition->size;
    switch(operandCount) {
        case 0: {
            return definition->name;
        }
        case 1: {
            std::ostringstream oss;
            oss << operands.at(0);
            return definition->name + " " + oss.str();
        }
        case 2: {
            std::ostringstream oss;
            oss << operands.at(0);
            oss << " ";
            oss << operands.at(1);
            return definition->name + " " + oss.str();
        }
    }
    return "ERROR: unhandled operandCount for " + definition->name;
}
