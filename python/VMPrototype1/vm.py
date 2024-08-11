from typing import Optional

from bytecode import Bytecode
from code_ad import read_uint16
from objects import AdObject, AdObjectInteger, AdBoolean, AdObjectType, AdNullObject
from opcode_ad import OpCodeByte
from settings import PRINT_LAST_ELEMENT_ON_STACK

NULL_OBJECT = AdNullObject()
TRUE = AdBoolean(value=True)
FALSE = AdBoolean(value=False)


class VM:
    def __init__(self, instructions=None, constants=None):
        self.instructions = instructions
        self.constants = constants
        self.stack = [None] * 1024
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
            elif opcode == OpCodeByte.OP_SUB:
                right = self.pop()
                left = self.pop()

                right_value = right.value
                left_value = left.value
                result = left_value - right_value
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
            elif opcode == OpCodeByte.OP_DIVIDE:
                right = self.pop()
                left = self.pop()

                right_value = right.value
                left_value = left.value
                result = left_value / right_value
                obj = AdObjectInteger(int(result))
                self.push(obj)
            elif opcode == OpCodeByte.OP_TRUE:
                obj = self.native_bool_to_boolean_object(True)
                self.push(obj)
            elif opcode == OpCodeByte.OP_FALSE:
                obj = self.native_bool_to_boolean_object(False)
                self.push(obj)
            elif opcode == OpCodeByte.OP_POP:
                if PRINT_LAST_ELEMENT_ON_STACK:
                    if self.sp == 1:
                        res = self.pop()
                        print(res.inspect())
                else:
                    self.pop()
            elif opcode == OpCodeByte.OP_EQUAL:
                self.execute_comparison(opcode)
            elif opcode == OpCodeByte.OP_NOTEQUAL:
                self.execute_comparison(opcode)
            elif opcode == OpCodeByte.OP_GREATERTHAN:
                self.execute_comparison(opcode)
            elif opcode == OpCodeByte.OP_GREATERTHAN_EQUAL:
                self.execute_comparison(opcode)
            elif opcode == OpCodeByte.OP_BANG:
                self.execute_bang_operator()
            elif opcode == OpCodeByte.OP_MINUS:
                self.execute_minus_operator()
            elif opcode == OpCodeByte.OP_JUMP:
                pos = read_uint16(self.instructions, ip + 1)
                ip = pos - 1
            elif opcode == OpCodeByte.OP_JUMP_NOT_TRUTHY:
                pos = read_uint16(self.instructions, ip + 1)
                ip += 2

                condition = self.pop()
                if not self.is_truthy(condition):
                    ip = pos - 1
            elif opcode == OpCodeByte.OP_NULL:
                self.push(NULL_OBJECT)
            else:
                print('severe error: vm.run() error')
            ip += 1

    def last_popped_stack_element(self) -> Optional[AdObject]:
        if self.sp == 0:
            return None
        return self.stack[self.sp - 1]

    def last_popped_stack_elem(self) -> Optional[AdObject]:
        return self.stack[self.sp]

    def print_stack_old(self):
        print([elem.inspect() for elem in self.stack if elem])

    def print_stack(self):
        i = 0
        print('[', end='')
        while i < self.sp:
            print(self.stack[i].inspect())
            i += 1
            if i < self.sp:
                print(', ', end='')
        print(']')

    def push(self, obj: AdObject):
        if self.sp < 0:
            raise Exception("stack error: index out of bounds")
        self.stack[self.sp] = obj
        self.sp += 1
        # self.stack.append(obj)

    def pop(self) -> AdObject:
        if self.sp - 1 < 0:
            raise Exception("stack error: index out of bounds")
        result = self.stack[self.sp - 1]
        # result = self.stack.pop()
        self.sp -= 1
        return result

    def execute_comparison(self, opcode):
        right = self.pop()
        left = self.pop()

        if left.object_type == AdObjectType.INT and right.object_type == AdObjectType.INT:
            return self.execute_integer_comparison(opcode, left, right)

        if opcode == OpCodeByte.OP_EQUAL:
            self.push(self.native_bool_to_boolean_object(left == right))
        elif opcode == OpCodeByte.OP_NOTEQUAL:
            self.push(self.native_bool_to_boolean_object(left != right))
        else:
            print('error: unknown operator')

    def execute_integer_comparison(self, opcode, left, right):
        if opcode == OpCodeByte.OP_EQUAL:
            self.push(self.native_bool_to_boolean_object(left.value == right.value))
        if opcode == OpCodeByte.OP_NOTEQUAL:
            self.push(self.native_bool_to_boolean_object(left.value != right.value))
        if opcode == OpCodeByte.OP_GREATERTHAN:
            self.push(self.native_bool_to_boolean_object(left.value > right.value))
        if opcode == OpCodeByte.OP_GREATERTHAN_EQUAL:
            self.push(self.native_bool_to_boolean_object(left.value >= right.value))

    def execute_bang_operator(self):
        operand = self.pop()

        if operand == TRUE:
            self.push(FALSE)
        elif operand == FALSE:
            self.push(TRUE)
        elif operand == NULL_OBJECT:
            self.push(TRUE)
        else:
            self.push(FALSE)

    def execute_minus_operator(self):
        operand = self.pop()

        if operand.object_type != AdObjectType.INT:
            print("unsupported type negation")

        value = operand.value
        self.push(AdObjectInteger(-value))

    def native_bool_to_boolean_object(self, value):
        if value:
            return TRUE
        return FALSE

    def is_truthy(self, obj) -> bool:
        if obj.object_type == AdObjectType.BOOL:
            return obj.value
        if obj.object_type == AdObjectType.NULL:
            return False
        return True
