from bytecode import Bytecode
from objects import AdObject


class VM:
    def __init__(self, instructions=None, constants=None):
        self.instructions = instructions
        self.constants = constants
        self.stack = []
        self.sp = 0

    def load(self, bytecode: Bytecode):
        self.instructions = bytecode.instructions
        self.constants = self.constants

    def run(self):
        pass

    def last_popped_stack_element(self):
        pass

    def push(self, obj: AdObject):
        self.sp += 1
        self.stack.append(obj)

    def pop(self) -> AdObject:
        result = self.stack[self.sp - 1]
        self.sp -= 1
        return result
