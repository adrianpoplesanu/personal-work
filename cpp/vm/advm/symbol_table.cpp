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

Symbol SymbolTable::define(std::string name) {
    Symbol symbol = Symbol(name, globalScope, numDefinitions);
    if (outer == nullptr) {
        symbol.scope = globalScope;
    } else {
        symbol.scope = localScope;
    }
    store[name] = symbol;
    ++numDefinitions;
    return symbol;
}

Symbol SymbolTable::resolve(std::string name) {
    Symbol obj = store[name];
    if (obj.scope.scope == "" && outer != nullptr) { // TODO: check this, i'm not sure
        obj = outer->resolve(name);
    }
    return obj;
}

SymbolTable* newSymbolTable() {
    return new SymbolTable();
}

SymbolTable* newEnclosedSymbolTable(SymbolTable *outer) {
    SymbolTable *s = newSymbolTable();
    s->outer = outer;
    return s;
}