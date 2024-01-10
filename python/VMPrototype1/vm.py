from typing import Optional

from bytecode import Bytecode
from code_ad import read_uint16
from objects import AdObject, AdObjectInteger
from opcode_ad import OpCodeByte


class VM:
    def __init__(self, instructions=None, constants=None):
        self.instructions = instructions
        self.constants = constants
        self.stack = []
        self.sp = 0

    def load(self, bytecode: Bytecode):
        self.instructions = bytecode.instructions
        self.constants = bytecode.constants

    def run(self):
        ip = 0
        while ip < len(self.instructions.bytes):
            opcode = self.instructions.bytes[ip]
            if opcode == OpCodeByte.OP_CONSTANT:
                const_index = read_uint16(self.instructions, ip + 1)
                ip += 2
                self.push(self.constants[const_index])
            elif opcode == OpCodeByte.OP_ADD:
                right = self.pop()
                left = self.pop()

                right_value = right.value
                left_value = left.value
                result = right_value + left_value
                obj = AdObjectInteger(result)
                self.push(obj)
            elif opcode == OpCodeByte.OP_MULTIPLY:
                right = self.pop()
                left = self.pop()

                right_value = right.value
                left_value = left.value
                result = right_value * left_value
                obj = AdObjectInteger(result)
                self.push(obj)
            else:
                print('severe error')
            ip += 1

    def last_popped_stack_element(self) -> Optional[AdObject]:
        if self.sp == 0:
            return None
        return self.stack[self.sp - 1]

    def push(self, obj: AdObject):
        self.sp += 1
        self.stack.append(obj)

    def pop(self) -> AdObject:
        # result = self.stack[self.sp - 1]
        result = self.stack.pop()
        self.sp -= 1
        return result
