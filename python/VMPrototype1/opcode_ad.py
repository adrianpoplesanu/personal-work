class OpCodeByte:
    OP_CONSTANT = 0
    OP_ADD = 1
    OP_SUB = 2
    OP_MULTIPLY = 3
    OP_DIVIDE = 4
    OP_POP = 5
    OP_TRUE = 6
    OP_FALSE = 7
    OP_EQUAL = 8
    OP_NOTEQUAL = 9
    OP_GREATERTHAN = 10
    OP_GREATERTHAN_EQUAL = 11
    OP_BANG = 12
    OP_MINUS = 13
    OP_JUMP_NOT_TRUTHY = 14
    OP_JUMP = 15
    OP_NULL = 16
    OP_GET_GLOBAL = 17
    OP_SET_GLOBAL = 18


class OpCode:
    byte_code = None


class OpConstant(OpCode):
    byte_code = OpCodeByte.OP_CONSTANT


class OpAdd(OpCode):
    byte_code = OpCodeByte.OP_ADD


class OpSub(OpCode):
    byte_code = OpCodeByte.OP_SUB


class OpMultiply(OpCode):
    byte_code = OpCodeByte.OP_MULTIPLY


class OpDivide(OpCode):
    byte_code = OpCodeByte.OP_DIVIDE


class OpPop(OpCode):
    byte_code = OpCodeByte.OP_POP


class OpTrue(OpCode):
    byte_code = OpCodeByte.OP_TRUE


class OpFalse(OpCode):
    byte_code = OpCodeByte.OP_FALSE


class OpEqual(OpCode):
    byte_code = OpCodeByte.OP_EQUAL


class OpNotEqual(OpCode):
    byte_code = OpCodeByte.OP_NOTEQUAL


class OpGreaterThan(OpCode):
    byte_code = OpCodeByte.OP_GREATERTHAN


class OpGreaterThanEqual(OpCode):
    byte_code = OpCodeByte.OP_GREATERTHAN_EQUAL


class OpBang(OpCode):
    byte_code = OpCodeByte.OP_BANG


class OpMinus(OpCode):
    byte_code = OpCodeByte.OP_MINUS


class OpJumpNotTruthy(OpCode):
    byte_code = OpCodeByte.OP_JUMP_NOT_TRUTHY


class OpJump(OpCode):
    byte_code = OpCodeByte.OP_JUMP


class OpNull(OpCode):
    byte_code = OpCodeByte.OP_NULL


op_constant = OpConstant()
op_add = OpAdd()
op_sub = OpSub()
op_multiply = OpMultiply()
op_divide = OpDivide()
op_pop = OpPop()
op_true = OpTrue()
op_false = OpFalse()
op_equal = OpEqual()
op_not_equal = OpNotEqual()
op_greater_than = OpGreaterThan()
op_greater_than_equal = OpGreaterThanEqual()
op_bang = OpBang()
op_minus = OpMinus()
op_jump_not_truthy = OpJumpNotTruthy()
op_jump = OpJump()
op_null = OpNull()
