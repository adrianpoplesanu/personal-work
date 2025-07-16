from code_ad import read_operands, format_int, format_instruction
from definition import Definition
from instructions import Instructions
from opcode_ad import OpCodeByte

definitions_map = {
    OpCodeByte.OP_CONSTANT: Definition("OpConstant", 1, [2]),
    OpCodeByte.OP_ADD: Definition("OpAdd", 0, []),
    OpCodeByte.OP_SUB: Definition("OpSub", 0, []),
    OpCodeByte.OP_MULTIPLY: Definition("OpMultiply", 0, []),
    OpCodeByte.OP_DIVIDE: Definition("OpDivide", 0, []),
    OpCodeByte.OP_POP: Definition("OpPop", 0, []),
    OpCodeByte.OP_TRUE: Definition("OpTrue", 0, []),
    OpCodeByte.OP_FALSE: Definition("OpFalse", 0, []),
    OpCodeByte.OP_EQUAL: Definition("OpEqual", 0, []),
    OpCodeByte.OP_NOTEQUAL: Definition("OpNotEqual", 0, []),
    OpCodeByte.OP_GREATERTHAN: Definition("OpGreaterThan", 0, []),
    OpCodeByte.OP_GREATERTHAN_EQUAL: Definition("OpGreaterThanEqual", 0, []),
    OpCodeByte.OP_MINUS: Definition("OpMinus", 0, []),
    OpCodeByte.OP_BANG: Definition("OpBang", 0, []),
    OpCodeByte.OP_JUMP_NOT_TRUTHY: Definition("OpJumpNotTruthy", 1, [2]),
    OpCodeByte.OP_JUMP: Definition("OpJump", 1, [2]),
    OpCodeByte.OP_NULL: Definition("OpNull", 0, []),
    OpCodeByte.OP_GET_GLOBAL: Definition("OpGetGlobal", 1, [2]),
    OpCodeByte.OP_SET_GLOBAL: Definition("OpSetGlobal", 1, [2]),
    OpCodeByte.OP_ARRAY: Definition("OpArray", 1, [2]),
    OpCodeByte.OP_HASH: Definition("OpHash", 1, [2]),
    OpCodeByte.OP_INDEX: Definition("OpIndex", 0, []),
    OpCodeByte.OP_CALL: Definition("OpCall", 1, [1]),
    OpCodeByte.OP_RETURN_VALUE: Definition("OpReturnValue", 0, []),
    OpCodeByte.OP_RETURN: Definition("OpReturn", 0, []),
    OpCodeByte.OP_GET_LOCAL: Definition("OpGetLocal", 1, [1]),
    OpCodeByte.OP_SET_LOCAL: Definition("OpSetLocal", 1, [1]),
    OpCodeByte.OP_GET_BUILTIN: Definition("OpGetBuiltin", 1, [1]),
    OpCodeByte.OP_CLOSURE: Definition("OpClosure", 2, [2, 1]),
    OpCodeByte.OP_GET_FREE: Definition("OpGetFree", 1, [1]),
    OpCodeByte.OP_CURRENT_CLOSURE: Definition("OpCurrentClosure", 0, []),
    OpCodeByte.OP_CLASS: Definition("OpClass", 0, []),
    OpCodeByte.OP_SET_METHOD: Definition("OpSetMethod", 0, []),
    OpCodeByte.OP_GET_PROPERTY: Definition("OpGetProperty", 0, []),
    OpCodeByte.OP_SET_PROPERTY: Definition("OpSetProperty", 0, []),
    # cand o sa pasez symbol index, atunci va trebui size=1 si [2]
    # OpCodeByte.OP_SET_PROPERTY_SYM: Definition("OpSetPropertySym", 0, []) # ??? maibe 1 [2]???
    OpCodeByte.OP_SET_PROPERTY_SYM: Definition("OpSetPropertySym", 1, [2]),
    OpCodeByte.OP_GET_PROPERTY_SYM: Definition("OpGetPropertySym", 1, [2])
}


def lookup(_byte) -> Definition:
    return definitions_map[_byte]


def disassemble_instructions(instructions: Instructions):
    out = ''
    i = 0
    while i < instructions.size:
        definition = lookup(instructions.bytes[i])
        operands = []
        read = read_operands(definition, instructions, i + 1, operands)
        out += format_int(i) + " " + format_instruction(definition, operands) + '\n'
        i += 1 + read
    return out
