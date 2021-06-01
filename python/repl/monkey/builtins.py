from object import Builtin
from object import Integer
from object import String

def len_builtin(*args, **kwargs):
    if len(args) != 1:
        return None

    if type(args[0]) == String:
        return Integer(Value=len(args[0].value))
    return None

builtins_map = {
    'len': Builtin(builtin_function=len_builtin)
}