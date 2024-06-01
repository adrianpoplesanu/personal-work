#include "code.h"
#include <cstring>
#include <sstream>

Code::Code() {
    definitionsMap.insert(std::make_pair(OP_CONSTANT, new Definition("OpConstant", 1, new int[1] {2})));
    definitionsMap.insert(std::make_pair(OP_ADD, new Definition("OpAdd", 0, new int)));
    definitionsMap.insert(std::make_pair(OP_MINUS, new Definition("OpMinus", 0, new int)));
    definitionsMap.insert(std::make_pair(OP_MULTIPLY, new Definition("OpMultiply", 0, new int)));
    definitionsMap.insert(std::make_pair(OP_DIVIDE, new Definition("OpDivide", 0, new int)));
    definitionsMap.insert(std::make_pair(OP_POP, new Definition("OpPop", 0, new int)));
    definitionsMap.insert(std::make_pair(OP_TRUE, new Definition("OpTrue", 0, new int)));
    definitionsMap.insert(std::make_pair(OP_FALSE, new Definition("OpFalse", 0, new int)));
    definitionsMap.insert(std::make_pair(OP_GREATERTHAN, new Definition("OpGreaterThan", 0, new int)));
    definitionsMap.insert(std::make_pair(OP_EQUALS, new Definition("OpEquals", 0, new int)));
    definitionsMap.insert(std::make_pair(OP_GREATERTHANEQUAL, new Definition("OpGreaterThanEqual", 0, new int)));
}

Code::~Code() {
    for(std::map<unsigned char, Definition*>::iterator it = definitionsMap.begin(); it != definitionsMap.end(); it++) {
        delete it->second;
    }
}

unsigned char* Code::make(OpCode opCode, int n, std::vector<int> &args, int &size) {
    Definition *definition = lookup(opCode.byteCode);

    int instructionLen = 1;

    for (int i = 0; i < definition->size; i++) {
        instructionLen += definition->operandWidths[i];
    }

    unsigned char *instruction = new unsigned char[instructionLen];
    instruction[0] = opCode.byteCode;
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
    }
    return "ERROR: unhandled operandCount for " + definition->name;
}
