from typing import Dict, Optional, List


class SymbolScope:
    def __init__(self, scope: str = None):
        self.scope = scope


GlobalScope = SymbolScope("GLOBAL")
LocalScope = SymbolScope("LOCAL")
BuiltinScope = SymbolScope("BUILTIN")
FreeScope = SymbolScope("FREE")
FunctionScope = SymbolScope("FUNCTION")


class Symbol:
    def __init__(self, name: str = None, scope: SymbolScope = None, index: int = None):
        self.name = name
        self.scope = scope
        self.index = index


class SymbolTable:
    def __init__(self, store: Dict[str, Symbol] = None, free_symbols: List[Symbol] = None, num_definitions: int = None):
        self.outer: Optional[SymbolTable] = None
        self.store = store
        self.free_symbols = free_symbols
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
            if obj and (obj.scope == GlobalScope or obj.scope == BuiltinScope):
                return obj
            free = self.define_free(obj)
            return free
        return obj

    def define_builtin(self, index: int, name: str) -> Symbol:
        symbol = Symbol(name=name, index=index, scope=BuiltinScope)
        self.store[name] = symbol
        return symbol

    def define_free(self, original: Symbol) -> Symbol:
        self.free_symbols.append(original)
        symbol = Symbol(name=original.name, index=len(self.free_symbols) - 1)
        symbol.scope = FreeScope

        self.store[original.name] = symbol
        return symbol

    def define_function_name(self, name: str) -> Symbol:
        symbol = Symbol(name=name, index=0, scope=FunctionScope)
        self.store[name] = symbol
        return symbol

def new_symbol_table():
    store: Dict[str, Symbol] = {}
    free = []
    return SymbolTable(store=store, free_symbols=free, num_definitions=0)


def new_enclosed_symbol_table(outer: SymbolTable) -> SymbolTable:
    s = new_symbol_table()
    s.outer = outer
    return s
