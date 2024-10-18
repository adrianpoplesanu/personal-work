from typing import Optional, Dict

from bytecode import Bytecode
from code_ad import read_uint16
from hash_utils import HashKey
from objects import AdObject, AdObjectInteger, AdBoolean, AdObjectType, AdNullObject, AdString, AdList, HashPair, AdHash
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
        self.globals = [None] * 65536  # GlobalsSize

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
            elif opcode in (OpCodeByte.OP_ADD, OpCodeByte.OP_SUB, OpCodeByte.OP_MULTIPLY, OpCodeByte.OP_DIVIDE):
                self.execute_binary_operation(opcode)
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
            elif opcode == OpCodeByte.OP_SET_GLOBAL:
                global_index: int = read_uint16(self.instructions, ip + 1)
                ip += 2

                self.globals[global_index] = self.pop()
            elif opcode == OpCodeByte.OP_GET_GLOBAL:
                global_index: int = read_uint16(self.instructions, ip + 1)
                ip += 2

                self.push(self.globals[global_index])
            elif opcode == OpCodeByte.OP_ARRAY:
                numElements: int = read_uint16(self.instructions, ip + 1)
                ip += 2

                array_obj: AdObject = self.build_array(self.sp - numElements, self.sp)
                self.sp = self.sp - numElements

                self.push(array_obj)
            elif opcode == OpCodeByte.OP_HASH:
                numElements: int = read_uint16(self.instructions, ip + 1)
                ip += 2

                hash_obj = self.build_hash(self.sp - numElements, self.sp)
                self.sp = self.sp - numElements

                self.push(hash_obj)
            elif opcode == OpCodeByte.OP_INDEX:
                index = self.pop()
                left = self.pop()
                self.execute_index_expression(left, index)
            elif opcode == OpCodeByte.OP_CALL:
                print("todo: implement OP_CALL in vm.run()")
            elif opcode == OpCodeByte.OP_RETURN_VALUE:
                print("todo: implement OP_RETURN_VALUE in vm.run()")
            elif opcode == OpCodeByte.OP_RETURN:
                print("todo: implement OP_RETURN in vm.run()")
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

    def execute_binary_operation(self, opcode):
        right = self.pop()
        left = self.pop()

        right_type = right.object_type
        left_type = left.object_type

        if right_type == AdObjectType.INT and left_type == AdObjectType.INT:
            return self.execute_binary_integer_operation(opcode, right, left)
        if right_type == AdObjectType.STRING and left_type == AdObjectType.STRING:
            return self.execute_binary_string_operation(opcode, right, left)

    def execute_binary_integer_operation(self, opcode, right, left):
        right_value = right.value
        left_value = left.value

        result = AdObjectInteger()
        if opcode == OpCodeByte.OP_ADD:
            result.value = left_value + right_value
        elif opcode == OpCodeByte.OP_SUB:
            result.value = left_value - right_value
        elif opcode == OpCodeByte.OP_MULTIPLY:
            result.value = left_value * right_value
        elif opcode == OpCodeByte.OP_DIVIDE:
            result.value = int(left_value / right_value)

        self.push(result)

    def execute_binary_string_operation(self, opcode, right, left):
        right_value = right.value
        left_value = left.value

        result = AdString()
        if opcode == OpCodeByte.OP_ADD:
            result.value = str(left_value) + str(right_value)

        self.push(result)

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

    def build_array(self, start_index: int, end_index: int) -> AdObject:
        elements = []
        for i in range(start_index, end_index):
            elements.append(self.stack[i])
        return AdList(elements)

    def build_hash(self, start_index: int, end_index: int) -> AdObject:
        hashed_pairs: Dict[HashKey, HashPair] = {}
        for i in range(start_index, end_index, 2):
            key = self.stack[i]
            value = self.stack[i + 1]

            pair = HashPair(key=key, value=value)
            hashed_pairs[key.hash_key().value] = pair
        return AdHash(pairs=hashed_pairs)

    def execute_index_expression(self, left, index):
        if left.object_type == AdObjectType.LIST:
            return self.execute_array_index(left, index)
        if left.object_type == AdObjectType.HASH:
            return self.execute_hash_index(left, index)

    def execute_array_index(self, left: AdList, index):
        i = index.value
        max = len(left.elements)
        if i < 0 or i >= max:
            self.push(NULL_OBJECT)
        else:
            self.push(left.elements[i])

    def execute_hash_index(self, left: AdHash, index):
        hash_key = index.hash_key()
        pair = left.pairs[hash_key.value]
        if pair:
            self.push(pair.value)
        else:
            self.push(NULL_OBJECT)

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
