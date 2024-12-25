from typing import Dict

from objects import AdBuiltinObject, AdObjectType


def len_builtin(args):
    obj = args[0]
    if obj.object_type == AdObjectType.LIST:
        return len(obj.elements)
    return 0


builtins: Dict[str, AdBuiltinObject] = {
    'len': AdBuiltinObject(builtin_function=len_builtin)
}


def get_builtin_by_name(name) -> AdBuiltinObject:
    for k, v in builtins.items():
        if k == name:
            return v
