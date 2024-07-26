from ast import ASTNode, StatementType, statement_type_map
from bytecode import Bytecode
from code_ad import Code
from emitted_instruction import EmittedInstruction
from instructions import Instructions
from objects import AdObjectInteger, AdObject
from opcode_ad import OpAdd, OpSub, OpMultiply, OpDivide, OpConstant, OpTrue, OpFalse, OpPop, op_equal, op_not_equal, \
    op_greater_than, op_greater_than_equal, op_add, op_sub, op_multiply, op_divide, op_pop, op_bang, op_minus, \
    op_jump_not_truthy, OpCode


class Compiler:
    def __init__(self):
        self.instructions = None
        self.bytecode = None
        self.code = Code()
        self.constants = []
        self.last_instruction = None
        self.previous_instruction = None

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
            self.compile(node.condition)
            # bogus 9999 value
            args = []
            args.append(9999)
            jump_not_truthy_pos = self.emit(op_jump_not_truthy, 1, args)

            self.compile(node.consequence)

            if self.last_instruction_is_pop():
                self.remove_last_pop()

            after_consequence_pos = len(self.instructions.bytes)
            self.change_operand(jump_not_truthy_pos, after_consequence_pos)
        elif node.statement_type == StatementType.BLOCK_STATEMENT:
            for stmt in node.statements:
                self.compile(stmt)
        else:
            print("severe error: node type unknown " + statement_type_map[node.statement_type])

    def emit(self, opcode, n=0, args=None) -> int:
        if not args:
            args = []
        size, instruction = self.code.make(opcode, n, args)
        pos = self.add_instruction(size, instruction)
        self.set_last_instruction(opcode, pos)
        return pos

    def get_bytecode(self) -> Bytecode:
        bytecode = Bytecode()
        bytecode.instructions = self.instructions
        bytecode.constants = self.constants
        return bytecode

    def add_instruction(self, size: int, instruction) -> int:
        pos_new_instruction = len(self.instructions.bytes)
        for i in range(size):
            self.instructions.add(instruction[i])
        return pos_new_instruction

    def add_constant(self, obj: AdObject) -> int:
        self.constants.append(obj)
        return len(self.constants) - 1

    def set_last_instruction(self, op, pos) -> None:
        previous = self.last_instruction
        last = EmittedInstruction(op, pos)

        self.previous_instruction = previous
        self.last_instruction = last

    def last_instruction_is_pop(self) -> bool:
        return self.last_instruction.opcode == op_pop

    def remove_last_pop(self) -> None:
        self.instructions.remove_last()
        self.last_instruction = self.previous_instruction

    def replace_instruction(self, pos: int, new_instruction: tuple):
        # TODO: check if list is the correct type for new_instruction
        for i, element in enumerate(new_instruction[1]):
            self.instructions.bytes[pos + i] = new_instruction[1][i]

    def change_operand(self, op_pos: int, operand: int):
        op = OpCode()
        op.byte_code = self.instructions.bytes[op_pos]
        new_instruction = self.code.make(op, 1, [operand])
        self.replace_instruction(op_pos, new_instruction)
