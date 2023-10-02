#ifndef __OPCODE_H
#define __OPCODE_H

enum OpCodeByte {
    OP_CONSTANT,
    OP_ADD
};

class OpCode {
public:
    OpCodeByte byteCode;
};

class OpConstant : public OpCode {
public:
    OpConstant() {
        byteCode = OP_CONSTANT;
    }
};

class OpAdd : public OpCode {
public:
    OpAdd() {
        byteCode = OP_ADD;
    }
};

#endif