from typing import Tuple

from definition import Definition
from instructions import Instructions
from opcode_ad import OpCodeByte, OpCode


def read_uint16(instructions: Instructions, offset: int) -> int:
    return int.from_bytes([instructions.bytes[offset], instructions.bytes[offset + 1]], byteorder='big')

def read_uint8(instructions: Instructions, offset: int) -> int:
    return int.from_bytes([instructions.bytes[offset]], byteorder='big')


def int_to_bytes(param_int):
    print(param_int)
    return [0, 0, 0, 0]


def read_operands(definition: Definition, instructions, start, operands) -> int:
    offset = 0

    i = 0
    for w in range(definition.size):
        if definition.operand_widths[w] == 2:
            operands.append(read_uint16(instructions, start + offset))
        elif definition.operand_widths[w] == 1:
            operands.append(read_uint8(instructions, start + offset))
        offset += definition.operand_widths[w]
    return offset


def format_int(n: int) -> str:
    return "{0:04}".format(n)


def format_instruction(definition: Definition, operands) -> str:
    operand_count = len(definition.operand_widths) + 1
    if operand_count == 1:
        return definition.name
    elif operand_count == 2:
        return "{0} {1}".format(definition.name, operands[0])
    else:
        print("unknowm instruction format")


class Code:
    def __init__(self):
        self.instructions = Instructions()
        self.definitions_map = {
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
            OpCodeByte.OP_CALL: Definition("OpCall", 0, []),
            OpCodeByte.OP_RETURN_VALUE: Definition("OpReturnValue", 0, []),
            OpCodeByte.OP_RETURN: Definition("OpReturn", 0, []),
            OpCodeByte.OP_GET_LOCAL: Definition("OpGetLocal", 1, [1]),
            OpCodeByte.OP_SET_LOCAL: Definition("OpSetLocal", 1, [1])
        }

    def make(self, opcode: OpCode, n, args) -> Tuple[int, list]:
        # TODO: rename args to operands
        definition = self.lookup(opcode.byte_code)
        instruction_len = 1
        for i in range(definition.size):
            instruction_len += definition.operand_widths[i]
        instruction = [None] * instruction_len
        instruction[0] = opcode.byte_code

        offset = 1
        i = 0
        for j in range(n):
            width = definition.operand_widths[i]
            i += 1
            if width == 2:
                argument = args[j]
                # instruction[offset] = self.int_to_bytes(argument)[2]
                # instruction[offset + 1] = self.int_to_bytes(argument)[3]
                operand_bytes = argument.to_bytes(2, 'big')
                instruction[offset] = operand_bytes[0]
                instruction[offset + 1] = operand_bytes[1]
            elif width == 1:
                argument = args[j]
                operand_bytes = argument.to_bytes(1, 'big')
                instruction[offset] = operand_bytes[0]
            else:
                print("severe error: unknown width " + str(width))
            offset += width

        return instruction_len, instruction

    def lookup(self, _byte) -> Definition:
        return self.definitions_map[_byte]

    def to_string(self):
        out = ''
        i = 0
        while i < self.instructions.size:
            definition = self.lookup(self.instructions.bytes[i])
            operands = []
            read = read_operands(definition, self.instructions, i + 1, operands)
            out += format_int(i) + " " + format_instruction(definition, operands) + '\n'
            i += 1 + read
        return out
