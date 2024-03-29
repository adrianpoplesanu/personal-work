#ifndef __OPCODE_H
#define __OPCODE_H

enum OpCodeByte {
    OP_CONSTANT,
    OP_ADD,
    OP_MINUS,
    OP_MULTIPLY,
    OP_DIVIDE
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

class OpMinus : public OpCode {
public:
    OpMinus() {
        byteCode = OP_MINUS;
    }
};

class OpMultiply : public OpCode {
public:
    OpMultiply() {
        byteCode = OP_MULTIPLY;
    }
};

class OpDivide : public OpCode {
public:
    OpDivide() {
        byteCode = OP_DIVIDE;
    }
};

#endif