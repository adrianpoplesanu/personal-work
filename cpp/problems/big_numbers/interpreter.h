#ifndef __INTERPRETER_H
#define __INTERPRETER_H

#include <iostream>
using namespace std;

enum Command {
    UNKNOWN,
    EMPTY,
    VARIABLE_DECLARATION,
    PRINT_COMMAND,
    FOR_INSTRUCTION,
    SHOWALL
};

class CommandInterpreter {
private:
    string text;
    Command command_type; 
public:
    CommandInterpreter();
    CommandInterpreter(string);
    void Analyze();
    void Execute();
};

#endif
