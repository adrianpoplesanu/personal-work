from typing import List

from ast import ASTNode, StatementType, statement_type_map
from bytecode import Bytecode
from code_ad import Code
from compilation_scope import CompilationScope
from emitted_instruction import EmittedInstruction
from instructions import Instructions
from objects import AdObjectInteger, AdObject, AdString, AdCompiledFunction
from opcode_ad import OpAdd, OpSub, OpMultiply, OpDivide, OpConstant, OpTrue, OpFalse, OpPop, op_equal, op_not_equal, \
    op_greater_than, op_greater_than_equal, op_add, op_sub, op_multiply, op_divide, op_pop, op_bang, op_minus, \
    op_jump_not_truthy, OpCode, op_jump, op_null, op_set_global, op_get_global, op_constant, op_array, op_hash, \
    op_index, op_return_value, op_return
from symbol_table import new_symbol_table


class Compiler:
    def __init__(self):
        self.instructions = None
        self.bytecode = None
        self.code = Code()
        self.constants = []
        self.last_instruction = None
        self.previous_instruction = None
        self.symbol_table = new_symbol_table()
        main_scope: CompilationScope = CompilationScope(self.code.instructions)
        self.scopes: List[CompilationScope] = [main_scope]
        self.scope_index: int = 0

    def reset(self):
        self.instructions = Instructions()
        self.bytecode = Bytecode()

    def compile(self, node: ASTNode) -> None:
        if node is None:
            print("severe error: node is null")
        elif node.statement_type == StatementType.PROGRAM:
            for stmt in node.statements:
                self.compile(stmt)
        elif node.statement_type == StatementType.EXPRESSION_STATEMENT:
            if (node.expression):
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
            args = [9999]
            jump_not_truthy_pos = self.emit(op_jump_not_truthy, 1, args)

            self.compile(node.consequence)

            if self.last_instruction_is(op_pop):
                self.remove_last_pop()

            #  op_jump with bogus 9999 value
            args = [9999]
            jump_pos = self.emit(op_jump, 1, args)

            after_consequence_pos = self.current_instructions().size
            self.change_operand(jump_not_truthy_pos, after_consequence_pos)

            if node.alternative is None:
                self.emit(op_null, 0, [])
            else:
                self.compile(node.alternative)

                if self.last_instruction_is(op_pop):
                    self.remove_last_pop()

            after_alternative_pos = self.current_instructions().size
            self.change_operand(jump_pos, after_alternative_pos)
        elif node.statement_type == StatementType.BLOCK_STATEMENT:
            for stmt in node.statements:
                self.compile(stmt)
        elif node.statement_type == StatementType.NULL_EXPRESSION:
            self.emit(op_null, 0, [])
        elif node.statement_type == StatementType.LET_STATEMENT:
            self.compile(node.value)
            symbol = self.symbol_table.define(node.name.value)
            self.emit(op_set_global, 1, [symbol.index])
        elif node.statement_type == StatementType.IDENTIFIER:
            symbol = self.symbol_table.resolve(node.value)
            self.emit(op_get_global, 1, [symbol.index])
        elif node.statement_type == StatementType.STRING_LITERAL:
            string_obj = AdString(node.value)
            args = []
            args.append(self.add_constant(string_obj))
            self.emit(op_constant, 1, args)
        elif node.statement_type == StatementType.LIST_LITERAL:
            for el in node.elements:
                self.compile(el)
            args = []
            args.append(len(node.elements))
            self.emit(op_array, 1, args)
        elif node.statement_type == StatementType.HASH_LITERAL:
            keys = []
            for key in node.pairs.keys():
                keys.append(key)
            keys = sorted(keys, key=lambda x: str(x))
            for k in keys:
                self.compile(k)
                self.compile(node.pairs[k])
            args = []
            args.append(len(node.pairs) * 2)
            self.emit(op_hash, 1, args)
        elif node.statement_type == StatementType.INDEX_EXPRESSION:
            self.compile(node.left)
            self.compile(node.index)
            args = []
            self.emit(op_index, 0, args)
        elif node.statement_type == StatementType.FUNCTION_LITERAL:
            self.enter_scope()
            self.compile(node.body)
            if self.last_instruction_is(op_pop):
                self.replace_last_pop_with_return()
            if not self.last_instruction_is(op_return_value):
                args = []
                self.emit(op_return, 0, args)
            instructions = self.leave_scope()
            compiled_func = AdCompiledFunction()
            compiled_func.instructions = instructions
            args = []
            args.append(self.add_constant(compiled_func))
            self.emit(op_constant, 1, args)
        elif node.statement_type == StatementType.CALL_EXPRESSION:
            print("todo: handle call expressions in compiler")
        elif node.statement_type == StatementType.RETURN_STATEMENT:
            self.compile(node.value)
            args = []
            self.emit(op_return_value, 0, args)
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
        bytecode.instructions = self.current_instructions()
        bytecode.constants = self.constants
        return bytecode

    def current_instructions(self) -> Instructions:
        return self.scopes[self.scope_index].instructions

    def add_instruction(self, size: int, instruction) -> int:
        pos_new_instruction = self.current_instructions().size
        updated_instructions = Instructions()
        for x in self.current_instructions().bytes:
            updated_instructions.add(x)
        for i in range(size):
            updated_instructions.add(instruction[i])

        self.scopes[self.scope_index].instructions = updated_instructions
        return pos_new_instruction

    def add_constant(self, obj: AdObject) -> int:
        self.constants.append(obj)
        return len(self.constants) - 1

    def set_last_instruction(self, op, pos) -> None:
        previous = self.scopes[self.scope_index].last_instruction
        last = EmittedInstruction(op, pos)

        self.scopes[self.scope_index].previous_instruction = previous
        self.scopes[self.scope_index].last_instruction = last

    def last_instruction_is_pop(self) -> bool:
        return self.scopes[self.scope_index].last_instruction.opcode == op_pop

    def last_instruction_is(self, op: OpCode) -> bool:
        if self.current_instructions().size == 0:
            return False
        return self.scopes[self.scope_index].last_instruction.opcode == op

    def replace_last_pop_with_return(self):
        last_pos = self.scopes[self.scope_index].last_instruction.position
        instr_len, instr = self.code.make(op_return_value, 0, [])
        self.replace_instruction(last_pos, instr)
        self.scopes[self.scope_index].last_instruction.opcode = op_return_value

    def remove_last_pop(self) -> None:
        last = self.scopes[self.scope_index].last_instruction
        previous = self.scopes[self.scope_index].previous_instruction

        old = self.current_instructions().bytes
        new = old[:last.position]

        self.scopes[self.scope_index].instructions.bytes = new
        self.scopes[self.scope_index].instructions.size = last.position
        self.scopes[self.scope_index].last_instruction = previous

    def replace_instruction(self, pos: int, new_instruction: list):
        ins = self.current_instructions()
        for i, element in enumerate(new_instruction):
            ins.bytes[pos + i] = new_instruction[i]

    def change_operand(self, op_pos: int, operand: int):
        op = OpCode()
        op.byte_code = self.current_instructions().bytes[op_pos]
        size, new_instruction = self.code.make(op, 1, [operand])
        self.replace_instruction(op_pos, new_instruction)

    def enter_scope(self):
        scope = CompilationScope(self.instructions, EmittedInstruction(), EmittedInstruction())
        self.scopes.append(scope)
        self.scope_index += 1

    def leave_scope(self):
        instructions = self.current_instructions()

        self.scopes = self.scopes[:len(self.scopes) - 1]
        self.scope_index -= 1

        return instructions
