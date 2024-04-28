class OpCodeByte:
    OP_CONSTANT = 0
    OP_ADD = 1
    OP_MINUS = 2
    OP_MULTIPLY = 3
    OP_DIVIDE = 4
    OP_POP = 5
    OP_TRUE = 6
    OP_FALSE = 7


class OpCode:
    byte_code = None


class OpConstant(OpCode):
    byte_code = OpCodeByte.OP_CONSTANT


class OpAdd(OpCode):
    byte_code = OpCodeByte.OP_ADD


class OpMinus(OpCode):
    byte_code = OpCodeByte.OP_MINUS


class OpMultiply(OpCode):
    byte_code = OpCodeByte.OP_MULTIPLY


class OpDivide(OpCode):
    byte_code = OpCodeByte.OP_DIVIDE


class OpPop(OpCode):
    byte_code = OpCodeByte.OP_POP


class OpTrue(OpCode):
    byte_code = OpCodeByte.OP_TRUE


class OpFalse(OpCode):
    bytecode = OpCodeByte.OP_FALSE
