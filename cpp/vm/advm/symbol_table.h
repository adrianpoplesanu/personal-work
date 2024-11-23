#ifndef __SYMBOL_TABLE_H
#define __SYMBOL_TABLE_H

#include <iostream>
#include <map>

class SymbolScope {
public:
    std::string scope;

    SymbolScope();
    SymbolScope(std::string);
};

SymbolScope globalScope("GLOBAL");
SymbolScope localScope("LOCAL");

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

    SymbolTable();
    SymbolTable(std::map<std::string, Symbol>, int);

    Symbol define(std::string);
    Symbol resolve(std::string);
};

SymbolTable* newSymbolTable();
SymbolTable* newEnclosedSymbolTable(SymbolTable *outer);

#endif