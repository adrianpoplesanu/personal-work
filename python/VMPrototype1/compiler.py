from bytecode import Bytecode
from instructions import Instructions


class Compiler:
    def __init__(self):
        self.instructions = None
        self.bytecode = None

    def reset(self):
        self.instructions = Instructions()
        self.bytecode = Bytecode()

    def compile(self, program):
        pass

    def bytecode(self):
        pass
