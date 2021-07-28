from object import Builtin
from object import Integer
from object import String
from object import ArrayObject

def len_builtin(*args, **kwargs):
    if len(args) != 1:
        return None

    if type(args[0]) == String:
        return Integer(Value=len(args[0].value))
    if type(args[0]) == ArrayObject:
        return Integer(Value=len(args[0].elements))
    return None

builtins_map = {
    'len': Builtin(builtin_function=len_builtin)
}