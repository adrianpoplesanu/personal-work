#ifndef __INTERPRETER_H
#define __INTERPRETER_H

#include <iostream>
#include <ctime>
#include <map>
#include "big_number.h"
using namespace std;

enum Command {
    UNKNOWN,
    EMPTY,
    VARIABLE_ASSIGN,
    VARIABLE_REFERENCE,
    ASSIGN_SCALAR,
    NUMBER_REFERENCE,
    PRINT_COMMAND, // this might be the same as VARIABLE_REFERENCE, only with the twist of couting the variable
    FOR_INSTRUCTION,
    ADD_INSTRUCTION,
    SHOWALL // show all variable currently existing
};

class CommandInterpreter {
private:
    string text;
    Command command_type;
    clock_t start;
    clock_t end;
public:
    CommandInterpreter();
    CommandInterpreter(string);
    void Analyze();
    void Execute(map<string, BigNumber>&);
};

#endif
