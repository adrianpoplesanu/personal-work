from typing import List, Dict

from hash_utils import HashKey
from instructions import Instructions


class AdObjectType:
    INT = "INT"
    BOOL = "BOOL"
    NULL = "NULL"
    STRING = "STRING"
    LIST = "LIST"
    HASH = "HASH"
    COMPILED_FUNCTION = "COMPILED_FUNCTION"


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
