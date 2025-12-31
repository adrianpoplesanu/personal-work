from typing import List, Dict

from ad_ast import ASTNode, ASTIdentifier
from hash_utils import HashKey
from instructions import Instructions
from symbol_table import new_symbol_table, new_enclosed_symbol_table


class AdObjectType:
    INT = "INT"
    BOOL = "BOOL"
    NULL = "NULL"
    STRING = "STRING"
    LIST = "LIST"
    HASH = "HASH"
    COMPILED_FUNCTION = "COMPILED_FUNCTION"
    BUILTIN = "BUILTIN"
    CLOJURE_OBJECT = "CLOSURE"
    CLASS = "CLASS"
    COMPILED_CLASS = "COMPILED_CLASS"
    INSTANCE = "INSTANCE"
    COMPILED_INSTANCE = "COMPILED_INSTANCE"
    BOUND_METHOD = "BOUND_METHOD"


class AdObject:
    object_type = None
    value = None

    def inspect(self) -> str:
        return 'not implemented'


class AdObjectInteger(AdObject):
    def __init__(self, value: int = None):
        self.object_type = AdObjectType.INT
        self.value = value

    def inspect(self) -> str:
        return str(self.value)

    def hash_key(self):
        return HashKey(type=type, value=hash(self.value))


class AdBoolean(AdObject):
    def __init__(self, value: bool):
        self.object_type = AdObjectType.BOOL
        self.value = value

    def inspect(self) -> str:
        if self.value:
            return 'true'
        return 'false'


class AdString(AdObject):
    def __init__(self, value: str = None):
        self.object_type = AdObjectType.STRING
        self.value = value

    def inspect(self) -> str:
        return "'" + self.value + "'"

    def hash_key(self):
        return HashKey(type=type, value=hash(self.value))


class AdList(AdObject):
    def __init__(self, elements: List[AdObject]):
        self.object_type = AdObjectType.LIST
        self.elements = elements

    def inspect(self) -> str:
        out = '['
        out += ', '.join([element.inspect() for element in self.elements])
        out += ']'
        return out


class HashPair(object):
    def __init__(self, key=None, value=None):
        """
        todo: write this
        """
        self.key = key
        self.value = value


class AdHash(AdObject):

    def __init__(self, pairs=Dict):
        """
        todo: write this
        """
        self.object_type = AdObjectType.HASH
        self.pairs = pairs

    def inspect(self):
        out = "{"
        out += ', '.join(['{0}: {1}'.format(pair.key.inspect(), pair.value.inspect()) for pair in self.pairs.values()])
        out += "}"
        return out


class AdCompiledFunction(AdObject):
    def __init__(self, instructions: Instructions = None, num_locals: int = 0, num_parameters: int = 0):
        self.object_type = AdObjectType.COMPILED_FUNCTION
        self.instructions = instructions
        self.num_locals = num_locals
        self.num_parameters = num_parameters

    def inspect(self) -> str:
        return "todo: implement AdCompiledFunction.inspect()"


class AdNullObject(AdObject):
    def __init__(self):
        self.object_type = AdObjectType.NULL

    def inspect(self) -> str:
        return "null"


class AdBuiltinObject(AdObject):
    def __init__(self, builtin_function=None, env=None, accepted_parameters_size=None):
        """
        @param builtin_function: reference to a function
        """
        self.object_type = AdObjectType.BUILTIN
        self.builtin_function = builtin_function
        self.env = env
        if accepted_parameters_size:
            self.accepted_parameters_size = accepted_parameters_size
        else:
            self.accepted_parameters_size = []

    def inspect(self) -> str:
        return "AdBuiltinObject"


class AdClosureObject(AdObject):
    def __init__(self, fn: AdCompiledFunction = None, free: List[AdObject] = None):
        self.object_type = AdObjectType.CLOJURE_OBJECT
        self.fn = fn
        self.free = free

    def inspect(self) -> str:
        return "todo: implement AdClosureObject.inspect()"


class AdClassObject(AdObject):
    # type = ObjectType.CLASS

    def __init__(self, name: ASTIdentifier = None, attributes: List[ASTNode] = None, methods: List[ASTNode] = None,
                 inherit_from: List[ASTNode] = None):
        """
        @param: name
        @param: attributes - after parsing
        @param: methods - after parsing
        @param: inherit_from - classes inherited after parsing
        """
        self.object_type = AdObjectType.CLASS
        self.name = name
        self.attributes = attributes
        self.methods = methods
        self.inherit_from = inherit_from

    def inspect(self):
        out = "<class object at memory address: " + str(hex(id(self))) + ">"
        return out


class AdCompiledClassObject(AdObject):
    def __init__(self, name: ASTIdentifier = None, methods: Dict[str, AdClosureObject] = None,
                 field_initializers: List[AdCompiledFunction] = None,
                 initializer_count: int = None,
                 constructor: AdClosureObject = None, super_class = None, outer_symbol_table = None):
        """
        :param name: ASTIdentifier - class name
        :param methods: map of AdClosureObject - method name points to associated AdClosureObject method
        :param field_initializers: list of AdClosureObject - if no constructor then these all need to be run
        :param initializer_count: int - number of fields that are initialized withing the class body
        :param constructor: AdClosureObject - method that gets called when instantiating, if it exists
        :param super_class: AdCompiledClassObject - inherited class
        """
        self.object_type = AdObjectType.COMPILED_CLASS
        self.name = name
        if methods:
            self.methods = methods
        else:
            self.methods = {}
        if field_initializers:
            self.field_initializers = field_initializers
        else:
            self.field_initializers = []
        self.initializer_count = initializer_count
        self.constructor = constructor
        self.super_class = super_class
        # TODO: aici s-ar putea sa am nevoie de un symbol table, pentru field-urile si metodele din clasa
        self.symbol_table = new_enclosed_symbol_table(outer_symbol_table) # oare e corect asa?

    def inspect(self) -> str:
        out = "<class object at memory address: " + str(hex(id(self))) + ">"
        return out


class AdCompiledInstance(AdObject):
    def __init__(self, table=None, klass=None, definition_num_args=None):
        self.object_type = AdObjectType.COMPILED_INSTANCE
        if table:
            self.table = table
        else:
            self.table = {}
        self.klass = klass
        self.definition_num_args = definition_num_args

    def inspect(self) -> str:
        return "todo: implement this in AdCompiledInstance"


class AdField(AdObject):
    pass


class AdBoundMethod(AdObject):
    def __init__(self, owner=None, bound_method=None):
        self.object_type = AdObjectType.BOUND_METHOD
        self.owner = owner
        self.bound_method = bound_method

    def inspect(self) -> str:
        return "todo: implement this in AdBoundMethod"
