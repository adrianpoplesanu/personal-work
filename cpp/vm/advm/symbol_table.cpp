#include "symbol_table.h"

SymbolScope::SymbolScope() {

}

SymbolScope::SymbolScope(std::string s) {
    scope = s;
}

Symbol::Symbol() {

}

Symbol::Symbol(std::string n, SymbolScope s, int i) {
    name = n;
    scope = s;
    index = i;
}

SymbolTable::SymbolTable() {
    store = std::map<std::string, Symbol>();
    numDefinitions = 0;
    outer = nullptr;
}

SymbolTable::SymbolTable(std::map<std::string, Symbol> s, int n) {
    store = s;
    numDefinitions = n;
    outer = nullptr;
}

SymbolTable::SymbolTable(std::map<std::string, Symbol> s, std::vector<Symbol> f_s, int n) {
    store = s;
    freeSymbols = f_s;
    numDefinitions = n;
    outer = nullptr;
}

Symbol SymbolTable::define(std::string name) {
    Symbol symbol;
    if (store.find(name) != store.end()) {
        symbol = resolve(name);
    } else {
        symbol = Symbol(name, globalScope, numDefinitions);
    }
    if (outer == nullptr) {
        symbol.scope = globalScope;
    } else {
        symbol.scope = localScope;
    }
    store[name] = symbol;
    ++numDefinitions;
    return symbol;
}

Symbol SymbolTable::defineFree(Symbol original) {
    freeSymbols.push_back(original);
    Symbol symbol = Symbol(original.name, freeScope, freeSymbols.size() - 1);

    store[original.name] = symbol;
    return symbol;
}

Symbol SymbolTable::defineFunctionName(std::string name) {
    Symbol symbol = Symbol(name, functionScope, 0);
    store[name] = symbol;
    return symbol;
}

Symbol SymbolTable::resolve(std::string name) {
    Symbol obj = store[name];
    if (obj.scope.scope == "" && outer != nullptr) { // TODO: check this, i'm not sure
        obj = outer->resolve(name);
        if (obj.scope.scope != "" && (obj.scope.scope == globalScope.scope || obj.scope.scope == builtinScope.scope)) {
            return obj;
        }
        if (obj.scope.scope == "") {
            std::cout << "ERROR: variable: " << name << " not found in scope\n";
            return obj; // TODO: is this correct? please check this
        }
        Symbol free = defineFree(obj);
        return free;
    }
    return obj;
}

Symbol SymbolTable::defineBuiltin(int index, std::string name) {
    Symbol symbol = Symbol(name, builtinScope, index);
    store[name] = symbol;
    return symbol;
}

SymbolTable* newSymbolTable() {
    return new SymbolTable();
}

SymbolTable* newEnclosedSymbolTable(SymbolTable *outer) {
    SymbolTable *s = newSymbolTable();
    s->outer = outer;
    return s;
}