#ifndef __SYMBOL_TABLE_H
#define __SYMBOL_TABLE_H

#include <iostream>
#include <map>
#include <vector>

class SymbolScope {
public:
    std::string scope;

    SymbolScope();
    SymbolScope(std::string);
};

SymbolScope globalScope("GLOBAL");
SymbolScope localScope("LOCAL");
SymbolScope builtinScope("BUILTIN");
SymbolScope freeScope("FREE");
SymbolScope functionScope("FUNCTION");

class Symbol {
public:
    std::string name;
    SymbolScope scope;
    int index;

    Symbol();
    Symbol(std::string, SymbolScope, int);
};

class SymbolTable {
public:
    SymbolTable *outer = nullptr;
    std::map<std::string, Symbol> store;
    int numDefinitions;
    std::vector<Symbol> freeSymbols;

    SymbolTable();
    SymbolTable(std::map<std::string, Symbol>, int);
    SymbolTable(std::map<std::string, Symbol>, std::vector<Symbol>, int);

    Symbol define(std::string);
    Symbol resolve(std::string);
    Symbol defineBuiltin(int, std::string);
    Symbol defineFunctionName(std::string);
    Symbol defineFree(Symbol);
};

SymbolTable* newSymbolTable();
SymbolTable* newEnclosedSymbolTable(SymbolTable *outer);

#endif