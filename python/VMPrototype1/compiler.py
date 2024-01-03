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
        instruction, size = self.code.make(size)
        pos = self.add_instruction(instruction)
        return pos

    def bytecode(self):
        pass

    def add_instruction(self, instruction) -> int:
        return 0

    def add_constant(self, obj: AdObject):
        pass
