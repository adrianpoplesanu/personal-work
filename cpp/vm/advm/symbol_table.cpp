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
}

SymbolTable::SymbolTable(std::map<std::string, Symbol> s, int n) {
    store = s;
    numDefinitions = n;
}

Symbol SymbolTable::define(std::string name) {
    Symbol symbol = Symbol(name, globalScope, numDefinitions);
    store[name] = symbol;
    ++numDefinitions;
    return symbol;
}

Symbol SymbolTable::resolve(std::string name) {
    return store[name];
}

SymbolTable newSymbolTable() {
    return SymbolTable();
}