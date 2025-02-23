from typing import Dict, List

from objects import AdBuiltinObject, AdObjectType, AdObjectInteger


def len_builtin(args):
    obj = args[0]
    if obj.object_type == AdObjectType.LIST:
        return AdObjectInteger(value=len(obj.elements))
    return AdObjectInteger(value=0)


def print_builtin(args):
    obj = args[0]
    print(obj.inspect(), end="")
    return None


def println_builtin(args):
    obj = args[0]
    print(obj.inspect())
    return None


builtins: List = [
    {'name': 'len', 'builtin': AdBuiltinObject(builtin_function=len_builtin)},
    {'name': 'print', 'builtin': AdBuiltinObject(builtin_function=print_builtin)},
    {'name': 'println', 'builtin': AdBuiltinObject(builtin_function=println_builtin)}
]


def get_builtin_by_name(name) -> AdBuiltinObject:
    for k, v in builtins.items():
        if k == name:
            return v
