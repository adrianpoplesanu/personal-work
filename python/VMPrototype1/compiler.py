from ast import ASTNode, StatementType, statement_type_map
from bytecode import Bytecode
from code_ad import Code
from instructions import Instructions
from objects import AdObjectInteger, AdObject
from opcode_ad import OpAdd, OpSub, OpMultiply, OpDivide, OpConstant, OpTrue, OpFalse, OpPop, op_equal, op_not_equal, \
    op_greater_than, op_greater_than_equal, op_add, op_sub, op_multiply, op_divide, op_pop, op_bang, op_minus


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
            print("severe error: node is null")
        elif node.statement_type == StatementType.PROGRAM:
            for stmt in node.statements:
                self.compile(stmt)
        elif node.statement_type == StatementType.EXPRESSION_STATEMENT:
            self.compile(node.expression)
            self.emit(op_pop, 0, [])
        elif node.statement_type == StatementType.PREFIX_EXPRESSION:
            self.compile(node.right)
            if node.operator == "!":
                self.emit(op_bang)
            elif node.operator == "-":
                self.emit(op_minus)
            else:
                print("SEVERE ERROR: prefix experssion")
        elif node.statement_type == StatementType.INFIX_EXPRESSION:
            if node.operator == '<':
                self.compile(node.right)
                self.compile(node.left)
                self.emit(op_greater_than)
                return None
            if node.operator == '<=':
                self.compile(node.right)
                self.compile(node.left)
                self.emit(op_greater_than_equal)
                return None

            self.compile(node.left)
            self.compile(node.right)
            if node.operator == '+':
                self.emit(op_add)
            elif node.operator == '-':
                self.emit(op_sub)
            elif node.operator == '*':
                self.emit(op_multiply)
            elif node.operator == '/':
                self.emit(op_divide)
            elif node.operator == '==':
                self.emit(op_equal)
            elif node.operator == '!=':
                self.emit(op_not_equal)
            elif node.operator == '>':
                self.emit(op_greater_than)
            elif node.operator == '>=':
                self.emit(op_greater_than_equal)
        elif node.statement_type == StatementType.INTEGER_LITERAL:
            integer_obj = AdObjectInteger(node.value)
            opcode = OpConstant()
            args = []
            args.append(self.add_constant(integer_obj))
            self.emit(opcode, 1, args)
        elif node.statement_type == StatementType.BOOLEAN:
            if node.value:
                opcode = OpTrue()
                self.emit(opcode, 0, [])
            else:
                opcode = OpFalse()
                self.emit(opcode, 0, [])
        elif node.statement_type == StatementType.IF_EXPRESSION:
            print("TODO: handle if expression")
        else:
            print("severe error: node type unknown " + statement_type_map[node.statement_type])

    def emit(self, opcode, n=0, args=None) -> int:
        if not args:
            args = []
        size, instruction = self.code.make(opcode, n, args)
        pos = self.add_instruction(size, instruction)
        return pos

    def get_bytecode(self) -> Bytecode:
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
