from typing import Dict


class SymbolScope:
    def __init__(self, scope: str = None):
        self.scope = scope


GlobalScope = SymbolScope("GLOBAL")


class Symbol:
    def __init__(self, name: str = None, scope: SymbolScope = None, index: int = None):
        self.name = name
        self.scope = scope
        self.index = index


class SymbolTable:
    def __init__(self, store: Dict[str, Symbol] = None, num_definitions: int = None):
        self.store = store
        self.num_definitions = num_definitions

    def define(self, name: str):
        symbol = Symbol(name=name, index=self.num_definitions, scope=GlobalScope)
        self.store[name] = symbol
        self.num_definitions += 1
        return symbol

    def resolve(self, name: str):
        obj = self.store[name]
        return obj


def new_symbol_table():
    store: Dict[str, Symbol] = {}
    return SymbolTable(store=store, num_definitions=0)
