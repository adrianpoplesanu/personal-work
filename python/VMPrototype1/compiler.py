from ast import ASTNode, StatementType, statement_type_map
from bytecode import Bytecode
from code_ad import Code
from instructions import Instructions
from objects import AdObjectInteger, AdObject
from opcode_ad import OpAdd, OpMinus, OpMultiply, OpDivide, OpConstant


class Compiler:
    def __init__(self):
        self.instructions = None
        self.bytecode = None
        self.code = Code()
        self.constants = []

    def reset(self):
        self.instructions = Instructions()
        self.bytecode = Bytecode()

    def compile(self, node: ASTNode):
        if node is None:
            print("severe error")
        elif node.statement_type == StatementType.PROGRAM:
            for stmt in node.statements:
                self.compile(stmt)
        elif node.statement_type == StatementType.EXPRESSION_STATEMENT:
            self.compile(node.expression)
        elif node.statement_type == StatementType.INFIX_EXPRESSION:
            self.compile(node.left)
            self.compile(node.right)
            if node.operator == '+':
                opcode = OpAdd()
                args = []
                self.emit(opcode, 0, args)
            elif node.operator == '-':
                opcode = OpMinus()
                args = []
                self.emit(opcode, 0, args)
            elif node.operator == '*':
                opcode = OpMultiply()
                args = []
                self.emit(opcode, 0, args)
            elif node.operator == '/':
                opcode = OpDivide()
                args = []
                self.emit(opcode, 0, args)
        elif node.statement_type == StatementType.INTEGER_LITERAL:
            integer_obj = AdObjectInteger(node.value)
            opcode = OpConstant()
            args = []
            args.append(self.add_constant(integer_obj))
            self.emit(opcode, 1, args)
        else:
            print("severe error: node type unknown " + statement_type_map[node.statement_type])

    def emit(self, opcode, n, args) -> int:
        size = 0
        size, instruction = self.code.make(size)
        pos = self.add_instruction(size, instruction)
        return pos

    def bytecode(self) -> Bytecode:
        bytecode = Bytecode()
        bytecode.instructions = self.instructions
        bytecode.constants = self.constants
        return bytecode

    def add_instruction(self, size: int, instruction) -> int:
        pos_new_instruction = size
        for i in range(size):
            self.instructions.add(instruction[i])
        return pos_new_instruction

    def add_constant(self, obj: AdObject) -> int:
        self.constants.append(obj)
        return len(self.constants) - 1
