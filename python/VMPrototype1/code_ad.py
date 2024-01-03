from definition import Definition
from opcode_ad import OpCodeByte


class Code:
    def __init__(self):
        self.definitions_map = {
            OpCodeByte.OP_CONSTANT: Definition("OpConstant", 1, [2]),
            OpCodeByte.OP_ADD: Definition("OpAdd", 0, []),
            OpCodeByte.OP_MINUS: Definition("OpMinus", 0, []),
            OpCodeByte.OP_MULTIPLY: Definition("OpMultiply", 0, []),
            OpCodeByte.OP_DIVIDE: Definition("OpDivide", 0, []),
        }

    def make(self, opcode, n, args, size):
        definition = self.lookup(opcode)
        return size, []

    def lookup(self, op) -> Definition:
        return self.definitions_map[op]
