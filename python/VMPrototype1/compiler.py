from typing import List

from ast import ASTNode, StatementType, statement_type_map
from builtins_ad import builtins
from bytecode import Bytecode
from code_ad import Code
from compilation_scope import CompilationScope
from emitted_instruction import EmittedInstruction
from instructions import Instructions
from objects import AdObjectInteger, AdObject, AdString, AdCompiledFunction, AdClassObject, AdCompiledClassObject
from opcode_ad import OpAdd, OpSub, OpMultiply, OpDivide, OpConstant, OpTrue, OpFalse, OpPop, op_equal, op_not_equal, \
    op_greater_than, op_greater_than_equal, op_add, op_sub, op_multiply, op_divide, op_pop, op_bang, op_minus, \
    op_jump_not_truthy, OpCode, op_jump, op_null, op_set_global, op_get_global, op_constant, op_array, op_hash, \
    op_index, op_return_value, op_return, op_call, op_set_local, op_get_local, op_get_builtin, op_closure, op_get_free, \
    op_current_closure, op_class, op_set_method, op_get_property, op_set_property, op_set_property_sym, \
    op_get_property_sym
from symbol_table import new_symbol_table, new_enclosed_symbol_table, GlobalScope, Symbol, LocalScope, BuiltinScope, \
    FreeScope, FunctionScope, ClassScope


class Compiler:
    def __init__(self):
        self.instructions = None
        self.bytecode = None
        self.code = Code()
        self.constants = []
        self.last_instruction = None
        self.previous_instruction = None
        self.symbol_table = new_symbol_table()
        i = 0
        for b in builtins:
            self.symbol_table.define_builtin(i, b['name'])
            i += 1
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
            if node.expression:
                if node.expression.statement_type == StatementType.DEF_STATEMENT:
                    # hmmm, dupa multe cautari am gasit fixul asta, ce ciudat mi se pare
                    self.compile(node.expression)
                elif node.expression.statement_type == StatementType.ASSIGN_STATEMENT:
                    self.compile(node.expression)
                elif node.expression.statement_type == StatementType.WHILE_EXPRESSION:
                    self.compile(node.expression)
                else:
                    self.compile(node.expression)
                    self.emit(op_pop, 0, [])
        elif node.statement_type == StatementType.PREFIX_EXPRESSION:
            self.compile(node.right)
            if node.operator == "!":
                self.emit(op_bang)
            elif node.operator == "-":
                self.emit(op_minus)
            else:
                print("SEVERE ERROR: prefix expression")
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
            symbol = self.symbol_table.define(node.name.value)
            self.compile(node.value)
            if symbol.scope == GlobalScope:
                self.emit(op_set_global, 1, [symbol.index])
            else:
                self.emit(op_set_local, 1, [symbol.index])
        elif node.statement_type == StatementType.IDENTIFIER:
            symbol = self.symbol_table.resolve(node.value)
            if symbol:
                self.load_symbol(symbol, node.value)
            else:
                # aici trebuie sa incerc sa handle un get value cu this implicit
                field = AdString(node.value)  # nu cred ca asta trebuie sa fie string, trebuie sa fie AdFieldAccess
                args = []
                args.append(self.add_constant(field))
                self.emit(op_constant, 1, args)
                self.emit(op_get_property_sym, 1, [0])
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

            if node.name:
                self.symbol_table.define_function_name(node.name)

            for p in node.parameters:
                self.symbol_table.define(p.value)
            self.compile(node.body)
            if self.last_instruction_is(op_pop):
                self.replace_last_pop_with_return()
            if not self.last_instruction_is(op_return_value):
                args = []
                self.emit(op_return, 0, args)
            free_symbols = self.symbol_table.free_symbols
            num_locals = self.symbol_table.num_definitions
            instructions = self.leave_scope()

            for s in free_symbols:
                self.load_symbol(s)

            compiled_func = AdCompiledFunction()
            compiled_func.instructions = instructions
            compiled_func.num_locals = num_locals
            compiled_func.num_parameters = len(node.parameters)
            args = []
            args.append(self.add_constant(compiled_func))
            args.append(len(free_symbols))
            self.emit(op_closure, 2, args)
        elif node.statement_type == StatementType.CALL_EXPRESSION:
            self.compile(node.func)
            for argument in node.arguments:
                self.compile(argument)
            args = [len(node.arguments)]
            self.emit(op_call, 1, args)
        elif node.statement_type == StatementType.RETURN_STATEMENT:
            self.compile(node.value)
            args = []
            self.emit(op_return_value, 0, args)
        elif node.statement_type == StatementType.DEF_STATEMENT:
            # am combinat LET_STATEMENT cu FUNCTION_LITERAL
            symbol = self.symbol_table.define(node.name.value)

            # aici e compile de function
            self.enter_scope()

            if node.name:
                self.symbol_table.define_function_name(node.name.value)

            for p in node.parameters:
                self.symbol_table.define(p.value)
            self.compile(node.body)
            if self.last_instruction_is(op_pop):
                self.replace_last_pop_with_return()
            if not self.last_instruction_is(op_return_value):
                args = []
                self.emit(op_return, 0, args)
            free_symbols = self.symbol_table.free_symbols
            num_locals = self.symbol_table.num_definitions
            instructions = self.leave_scope()

            for s in free_symbols:
                self.load_symbol(s)

            compiled_func = AdCompiledFunction()
            compiled_func.instructions = instructions
            compiled_func.num_locals = num_locals
            compiled_func.num_parameters = len(node.parameters)
            args = []
            args.append(self.add_constant(compiled_func))
            args.append(len(free_symbols))
            self.emit(op_closure, 2, args)
            # END aici e compile de function

            if symbol.scope == GlobalScope:
                self.emit(op_set_global, 1, [symbol.index])
            else:
                self.emit(op_set_local, 1, [symbol.index])
        elif node.statement_type == StatementType.ASSIGN_STATEMENT:
            if node.name.statement_type == StatementType.MEMBER_ACCESS:
                #pass
                self.compile(node.name.owner)
                symbol = self.symbol_table.resolve(node.name.member.token_literal())
                self.compile(node.value)

                field = AdString(node.name.member.token_literal())  # nu cred ca asta trebuie sa fie string, trebuie sa fie AdFieldAccess
                args = []
                args.append(self.add_constant(field))
                self.emit(op_constant, 1, args)

                # self.emit(op_set_property, 1, [symbol.index]) # cand o sa reusesc sa mapez corect symbol-ul
                #if symbol:
                self.emit(op_set_property, 0, [])
                #else:
                #    self.emit(op_set_property_implicit_this, 0, [])
            else:
                symbol = self.symbol_table.define(node.name.value)
                self.compile(node.value)
                if symbol.scope == GlobalScope:
                    self.emit(op_set_global, 1, [symbol.index])
                else:
                    self.emit(op_set_local, 1, [symbol.index])
        elif node.statement_type == StatementType.WHILE_EXPRESSION:
            start_pos = self.current_instructions().size
            self.compile(node.condition)
            # bogus 9999 value
            args = [9999]
            jump_not_truthy_pos = self.emit(op_jump_not_truthy, 1, args)

            self.compile(node.block)

            if self.last_instruction_is(op_pop):
                self.remove_last_pop()

            #  op_jump with bogus 9999 value
            args = [9999]
            jump_pos = self.emit(op_jump, 1, args)
            self.change_operand(jump_pos, start_pos)

            after_consequence_pos = self.current_instructions().size
            self.change_operand(jump_not_truthy_pos, after_consequence_pos)
        elif node.statement_type == StatementType.CLASS_STATEMENT:
            # combin let statement cu class
            symbol = self.symbol_table.define(node.name.value)

            ad_compiled_class_object = AdCompiledClassObject(name=node.name, outer_symbol_table=self.symbol_table)
            opcode = OpConstant()
            args = []
            args.append(self.add_constant(ad_compiled_class_object))
            self.emit(opcode, 1, args)

            self.emit(op_class, 0, [])

            if symbol.scope == GlobalScope:
                self.emit(op_set_global, 1, [symbol.index])
            else:
                self.emit(op_set_local, 1, [symbol.index])
            # for each method emit get global, emit op constant for method, compile(method), emit(op_set_method)
            self.load_symbol(symbol)

            previous_symbol_table = self.symbol_table
            self.symbol_table = ad_compiled_class_object.symbol_table
            #this_symbol = self.symbol_table.define("this")
            #self.symbol_table.define_class_name("this", symbol.class_index)

            for attribute in node.attributes:
                # symbol = ad_compiled_class_object.symbol_table.define(attribute.expression.name.value)
                attribute_symbol = self.symbol_table.define(attribute.expression.name.value)
                # previous_symbol_table.define_class_name(attribute.expression.name.value)
                self.symbol_table.define_class_name(attribute.expression.name.value, symbol.class_index)

                self.enter_scope()

                self.compile(attribute.expression.value)

                field = AdString(attribute.expression.name.value)  # nu cred ca asta trebuie sa fie string, trebuie sa fie AdFieldAccess
                args = []
                args.append(self.add_constant(field))
                self.emit(op_constant, 1, args)

                #self.emit(op_set_property_sym, 1, [symbol.index]) # maybe like this?
                self.emit(op_set_property_sym, 1, [attribute_symbol.index])
                #self.emit(op_return, 0, [])

                instructions = self.leave_scope()
                compiled_func = AdCompiledFunction()
                compiled_func.instructions = instructions
                compiled_func.num_locals = 0
                compiled_func.num_parameters = 0

                ad_compiled_class_object.field_initializers.append(compiled_func)

            for method in node.methods:
                # aici e compile de function
                self.enter_scope()

                this_symbol = self.symbol_table.define("this")
                self.symbol_table.define_class_name("this", symbol.class_index)

                #self.symbol_table.define("this")
                #self.symbol_table.define_class_name("this", symbol.class_index)

                if method.name:
                    self.symbol_table.define_class_name(method.name.value, symbol.class_index) # oare am nevoie de asta pentru recursivitate?

                for p in method.parameters:
                    self.symbol_table.define(p.value)
                self.compile(method.body)
                if self.last_instruction_is(op_pop):
                    self.replace_last_pop_with_return()
                if not self.last_instruction_is(op_return_value):
                    args = []
                    self.emit(op_return, 0, args)
                free_symbols = self.symbol_table.free_symbols
                num_locals = self.symbol_table.num_definitions
                instructions = self.leave_scope()

                #self.symbol_table.define_this("this", symbol.index)
                #self.symbol_table.define_class_name("this", symbol.class_index)

                for s in free_symbols:
                    self.load_symbol(s)

                compiled_func = AdCompiledFunction()
                compiled_func.instructions = instructions
                compiled_func.num_locals = num_locals
                compiled_func.num_parameters = len(method.parameters)
                args = []
                args.append(self.add_constant(compiled_func))
                args.append(len(free_symbols))
                self.emit(op_closure, 2, args)

                # i don't like this, maybe i should be using the symbol table
                method_name_constant = AdString(method.name.value)
                args = []
                args.append(self.add_constant(method_name_constant))
                self.emit(op_constant, 1, args)

                # END aici e compile de function

                args = []
                self.emit(op_set_method, 0, args)
            self.symbol_table = previous_symbol_table
        elif node.statement_type == StatementType.MEMBER_ACCESS:
            symbol = None
            if node.owner.statement_type == StatementType.THIS_EXPRESSION:
                symbol = self.symbol_table.resolve("this")
                symbol.scope = LocalScope
                if symbol:
                    self.load_symbol(symbol)
            else:
                symbol = self.symbol_table.resolve(node.owner.value)
                if symbol:
                    self.load_symbol(symbol)

            field = AdString(node.member) # nu cred ca asta trebuie sa fie string, trebuie sa fie AdFieldAccess
            args = []
            args.append(self.add_constant(field))
            self.emit(op_constant, 1, args)

            self.emit(op_get_property, 0, [])

            if node.is_method:
                #self.compile(node.func)
                for argument in node.arguments:
                    self.compile(argument)
                args = [len(node.arguments)]
                self.emit(op_call, 1, args)
        elif node.statement_type == StatementType.THIS_EXPRESSION:
            symbol = self.symbol_table.resolve("this")
            symbol.scope = LocalScope
            if symbol:
                self.load_symbol(symbol)
            #self.load_symbol(symbol)
            # print('i need to handle this this')
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
        self.symbol_table = new_enclosed_symbol_table(self.symbol_table)

    def leave_scope(self):
        instructions = self.current_instructions()

        self.scopes = self.scopes[:len(self.scopes) - 1]
        self.scope_index -= 1

        self.symbol_table = self.symbol_table.outer

        return instructions

    def load_symbol(self, symbol: Symbol, field_name: str = None):
        if symbol.scope == GlobalScope:
            self.emit(op_get_global, 1, [symbol.index])
        elif symbol.scope == LocalScope:
            self.emit(op_get_local, 1, [symbol.index])
        elif symbol.scope == BuiltinScope:
            self.emit(op_get_builtin, 1, [symbol.index])
        elif symbol.scope == FreeScope:
            self.emit(op_get_free, 1, [symbol.index])
        elif symbol.scope == ClassScope:
            field = AdString(field_name)
            args = []
            args.append(self.add_constant(field))
            self.emit(op_constant, 1, args)
            self.emit(op_get_property_sym, 1, [symbol.index])
        elif symbol.scope == FunctionScope:
            self.emit(op_current_closure, 0, [])
