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
    OP_ARRAY = 19
    OP_HASH = 20
    OP_INDEX = 21
    OP_CALL = 22
    OP_RETURN_VALUE = 23
    OP_RETURN = 24
    OP_GET_LOCAL = 25
    OP_SET_LOCAL = 26
    OP_GET_BUILTIN = 27
    OP_CLOSURE = 28
    OP_GET_FREE = 29
    OP_CURRENT_CLOSURE = 30

    OP_CLASS = 31
    OP_SET_METHOD = 32
    OP_INSTANTIATE = 33

    OP_GET_PROPERTY = 34
    OP_SET_PROPERTY = 35

    OP_GET_METHOD = 36
    OP_INVOKE = 37

    OP_SET_PROPERTY_SYM = 38
    OP_GET_PROPERTY_SYM = 39
    OP_PATCH_PROPERTY_SYM = 40


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


class OpGetGlobal(OpCode):
    byte_code = OpCodeByte.OP_GET_GLOBAL


class OpSetGlobal(OpCode):
    byte_code = OpCodeByte.OP_SET_GLOBAL


class OpArray(OpCode):
    byte_code = OpCodeByte.OP_ARRAY


class OpHash(OpCode):
    byte_code = OpCodeByte.OP_HASH


class OpIndex(OpCode):
    byte_code = OpCodeByte.OP_INDEX


class OpCall(OpCode):
    byte_code = OpCodeByte.OP_CALL


class OpReturnValue(OpCode):
    byte_code = OpCodeByte.OP_RETURN_VALUE


class OpReturn(OpCode):
    byte_code = OpCodeByte.OP_RETURN


class OpGetLocal(OpCode):
    byte_code = OpCodeByte.OP_GET_LOCAL


class OpSetLocal(OpCode):
    byte_code = OpCodeByte.OP_SET_LOCAL


class OpGetBuiltin(OpCode):
    byte_code = OpCodeByte.OP_GET_BUILTIN


class OpClosure(OpCode):
    byte_code = OpCodeByte.OP_CLOSURE


class OpGetFree(OpCode):
    byte_code = OpCodeByte.OP_GET_FREE


class OpCurrentClosure(OpClosure):
    byte_code = OpCodeByte.OP_CURRENT_CLOSURE


class OpClass(OpClosure):
    byte_code = OpCodeByte.OP_CLASS


class OpSetMethod(OpClosure):
    byte_code = OpCodeByte.OP_SET_METHOD


class OpGetProperty(OpCode):
    byte_code = OpCodeByte.OP_GET_PROPERTY


class OpSetProperty(OpCode):
    byte_code = OpCodeByte.OP_SET_PROPERTY


class OpSetPropertySym(OpCode):
    byte_code = OpCodeByte.OP_SET_PROPERTY_SYM


class OpGetPropertySym(OpCode):
    byte_code = OpCodeByte.OP_GET_PROPERTY_SYM


class OpPatchPropertySym(OpCode):
    byte_code = OpCodeByte.OP_PATCH_PROPERTY_SYM


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
op_get_global = OpGetGlobal()
op_set_global = OpSetGlobal()
op_array = OpArray()
op_hash = OpHash()
op_index = OpIndex()
op_call = OpCall()
op_return_value = OpReturnValue()
op_return = OpReturn()
op_get_local = OpGetLocal()
op_set_local = OpSetLocal()
op_get_builtin = OpGetBuiltin()
op_closure = OpClosure()
op_get_free = OpGetFree()
op_current_closure = OpCurrentClosure()
op_class = OpClass()
op_set_method = OpSetMethod()
op_get_property = OpGetProperty()
op_set_property = OpSetProperty()
op_get_property_sym = OpGetPropertySym()
op_set_property_sym = OpSetPropertySym()
op_patch_property_sym = OpPatchPropertySym()
