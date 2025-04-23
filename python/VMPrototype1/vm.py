from typing import Optional, Dict, List

from builtins_ad import builtins
from bytecode import Bytecode
from code_ad import read_uint16, read_uint8
from frame import Frame, new_frame
from hash_utils import HashKey
from objects import AdObject, AdObjectInteger, AdBoolean, AdObjectType, AdNullObject, AdString, AdList, HashPair, \
    AdHash, AdCompiledFunction, AdBuiltinObject, AdClosureObject, AdCompiledClassObject, AdCompiledInstance, \
    AdBoundMethod
from opcode_ad import OpCodeByte
from settings import PRINT_LAST_ELEMENT_ON_STACK

NULL_OBJECT = AdNullObject()
TRUE = AdBoolean(value=True)
FALSE = AdBoolean(value=False)


class VM:
    def __init__(self, instructions=None, constants=None):
        self.instructions = instructions
        self.constants = constants
        self.stack: List[Optional[AdObject]] = [None] * 1024
        self.sp: int = 0
        self.globals = [None] * 65536  # GlobalsSize
        self.frames: List[Optional[Frame]] = [None] * 1024
        self.frames_index: int = 0

    def load(self, bytecode: Bytecode):
        main_fn = AdCompiledFunction(instructions=bytecode.instructions)
        main_closure = AdClosureObject(fn=main_fn)
        main_frame = new_frame(main_closure, 0)

        # self.instructions = bytecode.instructions # remove-ul asta da peste cap run()
        self.constants = bytecode.constants

        self.stack = [None] * 1024
        self.sp = 0

        self.globals = [None] * 65536  # GlobalsSize

        self.frames[0] = main_frame
        self.frames_index = 1

    def run(self):
        while self.current_frame().ip < len(self.current_frame().instructions().bytes) - 1:
            self.current_frame().ip += 1
            ip = self.current_frame().ip
            ins = self.current_frame().instructions()
            opcode = ins.bytes[ip]
            if opcode == OpCodeByte.OP_CONSTANT:
                const_index = read_uint16(ins, ip + 1)
                self.current_frame().ip += 2
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
                pos = read_uint16(ins, ip + 1)
                self.current_frame().ip = pos - 1
            elif opcode == OpCodeByte.OP_JUMP_NOT_TRUTHY:
                pos = read_uint16(ins, ip + 1)
                self.current_frame().ip += 2

                condition = self.pop()
                if not self.is_truthy(condition):
                    self.current_frame().ip = pos - 1
            elif opcode == OpCodeByte.OP_NULL:
                self.push(NULL_OBJECT)
            elif opcode == OpCodeByte.OP_SET_GLOBAL:
                global_index: int = read_uint16(ins, ip + 1)
                self.current_frame().ip += 2

                self.globals[global_index] = self.pop()
            elif opcode == OpCodeByte.OP_GET_GLOBAL:
                global_index: int = read_uint16(ins, ip + 1)
                self.current_frame().ip += 2

                self.push(self.globals[global_index])
            elif opcode == OpCodeByte.OP_ARRAY:
                numElements: int = read_uint16(ins, ip + 1)
                self.current_frame().ip += 2

                array_obj: AdObject = self.build_array(self.sp - numElements, self.sp)
                self.sp = self.sp - numElements

                self.push(array_obj)
            elif opcode == OpCodeByte.OP_HASH:
                numElements: int = read_uint16(ins, ip + 1)
                self.current_frame().ip += 2

                hash_obj = self.build_hash(self.sp - numElements, self.sp)
                self.sp = self.sp - numElements

                self.push(hash_obj)
            elif opcode == OpCodeByte.OP_INDEX:
                index = self.pop()
                left = self.pop()
                self.execute_index_expression(left, index)
            elif opcode == OpCodeByte.OP_CALL:
                num_args = read_uint8(ins, ip + 1)
                self.current_frame().ip += 1
                #self.call_function(int(num_args))
                self.execute_call(int(num_args))
            elif opcode == OpCodeByte.OP_RETURN_VALUE:
                return_value = self.pop()
                frame = self.pop_frame()
                self.sp = frame.base_pointer - 1
                self.push(return_value)
            elif opcode == OpCodeByte.OP_RETURN:
                frame = self.pop_frame()
                self.sp = frame.base_pointer - 1
                self.push(NULL_OBJECT)
            elif opcode == OpCodeByte.OP_SET_LOCAL:
                local_index = read_uint8(ins, ip + 1)
                self.current_frame().ip += 1
                frame = self.current_frame()
                self.stack[frame.base_pointer + int(local_index)] = self.pop()
            elif opcode == OpCodeByte.OP_GET_LOCAL:
                local_index = read_uint8(ins, ip + 1)
                self.current_frame().ip += 1
                frame = self.current_frame()
                self.push(self.stack[frame.base_pointer + int(local_index)])
            elif opcode == OpCodeByte.OP_GET_BUILTIN:
                builtin_index = read_uint8(ins, ip + 1)
                self.current_frame().ip += 1
                definition = builtins[builtin_index]
                self.push(definition['builtin'])
            elif opcode == OpCodeByte.OP_CLOSURE:
                const_index = read_uint16(ins, ip + 1)
                num_free = read_uint8(ins, ip + 3)
                self.current_frame().ip += 3
                self.push_closure(int(const_index), num_free)
            elif opcode == OpCodeByte.OP_GET_FREE:
                free_index = read_uint8(ins, ip + 1)
                self.current_frame().ip += 1
                current_closure = self.current_frame().cl
                self.push(current_closure.free[free_index])
            elif opcode == OpCodeByte.OP_CURRENT_CLOSURE:
                current_closure = self.current_frame().cl
                self.push(current_closure)
            elif opcode == OpCodeByte.OP_CLASS:
                # print('TODO: need to vm.run() for OP_CLASS')
                # skipping vm.run() for class
                pass
            elif opcode == OpCodeByte.OP_SET_METHOD:
                method_name = self.pop()
                method_closure = self.pop()
                klass = self.pop()
                # TODO: add checks here
                klass.methods[method_name.value] = method_closure
                self.push(klass)
            elif opcode == OpCodeByte.OP_GET_PROPERTY:
                field_name = self.pop()
                owner = self.pop()

                # todo: asta nu e bine, field_name.value poate? table are cheie str, field_name e un AdObject, deci sigur nu e bine
                if owner.table.get(field_name.value.value) is not None:
                    #self.pop()
                    self.push(owner.table[field_name.value.value])
                if owner.klass.methods.get(field_name.value.value) is not None:
                    method_closure = owner.klass.methods[field_name.value.value]
                    bound_method = AdBoundMethod(owner, method_closure)
                    self.pop()
                    self.push(bound_method)
            elif opcode == OpCodeByte.OP_SET_PROPERTY:
                field = self.pop()
                value = self.pop()
                instance = self.pop()
                instance.table[field.value] = value
                self.push(value)
            elif opcode == OpCodeByte.OP_SET_PROPERTY_SYM:
                field = self.pop()
                value = self.pop()
                instance = self.pop()

                #if not isinstance(instance, InstanceObject):
                #    raise RuntimeError("Expected class instance")

                #instance.fields[symbolIndex] = value
                #push(value)
                instance.table[field.value] = value
                self.pop_frame()
                self.push(instance)
            else:
                print('severe error: vm.run() error')

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

    def current_frame(self) -> Frame:
        return self.frames[self.frames_index - 1]

    def push_frame(self, f: Frame):
        self.frames[self.frames_index] = f
        self.frames_index += 1

    def pop_frame(self) -> Frame:
        self.frames_index -= 1
        return self.frames[self.frames_index]

    def push_closure(self, const_index: int, num_free: int):
        constant = self.constants[const_index]
        function = constant
        free = [None] * num_free
        for i in range(num_free):
            free[i] = self.stack[self.sp - num_free + i]
        self.sp = self.sp - num_free

        closure = AdClosureObject(fn=function, free=free)
        self.push(closure)

    def execute_call(self, num_args: int):
        callee = self.stack[self.sp - 1 - num_args]
        if callee.object_type == AdObjectType.CLOJURE_OBJECT:
            self.call_closure(callee, num_args)
        elif callee.object_type == AdObjectType.BUILTIN:
            self.call_builtin(callee, num_args)
        elif callee.object_type == AdObjectType.COMPILED_CLASS:
            self.call_class(callee, num_args)
        elif callee.object_type == AdObjectType.BOUND_METHOD:
            self.call_bound_method(callee, num_args)
        else:
            print('SEVERE ERROR: calling error')

    def call_class(self, cl: AdCompiledClassObject, num_args):
        instance = AdCompiledInstance()
        instance.klass = cl
        instance.definition_num_args = num_args
        for field_initializer in instance.klass.field_initializers:
            #self.push(field_initializer)
            #self.call_function(0)
            closure = AdClosureObject(field_initializer)
            self.push(closure)
            #self.call_initializer(closure, 0)
            self.execute_call(0)
            #self.pop_frame()
        self.push(instance)

    def call_bound_method(self, cl: AdBoundMethod, num_args):
        if num_args != cl.bound_method.fn.num_parameters:
            print("ERROR: wrong number of arguments expecting: {0} got: {1}".format(cl.fn.num_parameters, num_args))

        frame = new_frame(cl.bound_method, self.sp - num_args)
        self.push_frame(frame)
        self.sp = frame.base_pointer + cl.bound_method.fn.num_locals

        return None

    def call_closure(self, cl: AdClosureObject, num_args):
        # fn: AdCompiledFunction = self.stack[self.sp - 1 - int(num_args)]

        if num_args != cl.fn.num_parameters:
            print("ERROR: wrong number of arguments expecting: {0} got: {1}".format(cl.fn.num_parameters, num_args))

        frame = new_frame(cl, self.sp - num_args)
        self.push_frame(frame)
        self.sp = frame.base_pointer + cl.fn.num_locals

        return None

    def call_builtin(self, builtin: AdBuiltinObject, num_args: int):
        args = self.stack[self.sp - num_args: self.sp]
        result = builtin.builtin_function(args)
        self.sp = self.sp - num_args - 1

        if result is not None:
            self.push(result)
        else:
            self.push(NULL_OBJECT)
        return None

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
