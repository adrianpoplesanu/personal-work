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
        # TODO: am adaugat if-ul asta ca sa nu generez simboluri noi pentru acelasi identificator
        # ca sa pot sa fac i = 5 i = i + 1, a doua atribuire creeaza un simbol nou cu index 1, si i + 1 nu stii ce e
        if name in self.store:
            symbol = self.resolve(name)
        else:
            symbol = Symbol(name=name, index=self.num_definitions)
        if self.outer is None:
            symbol.scope = GlobalScope
        else:
            symbol.scope = LocalScope
        self.store[name] = symbol
        self.num_definitions += 1
        return symbol

    def resolve(self, name: str) -> Optional[Symbol]:
        obj = self.store.get(name)
        if obj is None and self.outer:
            obj = self.outer.resolve(name)
            if obj and (obj.scope == GlobalScope or obj.scope == BuiltinScope):
                return obj
            if obj is None:
                print("ERROR: variable: {0} not found in scope".format(name))
                # TODO: is this correct? please check this
                return None
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
