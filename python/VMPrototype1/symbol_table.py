from typing import Dict, Optional


class SymbolScope:
    def __init__(self, scope: str = None):
        self.scope = scope


GlobalScope = SymbolScope("GLOBAL")
LocalScope = SymbolScope("LOCAL")
BuiltinScope = SymbolScope("BUILTIN")


class Symbol:
    def __init__(self, name: str = None, scope: SymbolScope = None, index: int = None):
        self.name = name
        self.scope = scope
        self.index = index


class SymbolTable:
    def __init__(self, store: Dict[str, Symbol] = None, num_definitions: int = None):
        self.outer: Optional[SymbolTable] = None
        self.store = store
        self.num_definitions = num_definitions

    def define(self, name: str):
        symbol = Symbol(name=name, index=self.num_definitions)
        if self.outer is None:
            symbol.scope = GlobalScope
        else:
            symbol.scope = LocalScope
        self.store[name] = symbol
        self.num_definitions += 1
        return symbol

    def resolve(self, name: str):
        obj = self.store.get(name)
        if obj is None and self.outer:
            obj = self.outer.resolve(name)
        return obj

    def define_builtin(self, index: int, name: str) -> Symbol:
        symbol = Symbol(name=name, index=index, scope=BuiltinScope)
        self.store[name] = symbol
        return symbol


def new_symbol_table():
    store: Dict[str, Symbol] = {}
    return SymbolTable(store=store, num_definitions=0)


def new_enclosed_symbol_table(outer: SymbolTable) -> SymbolTable:
    s = new_symbol_table()
    s.outer = outer
    return s
