#include "program.h"
#include "interpreter.h"

#include <iostream>
#include <string>
using namespace std;

Program::Program() {
    //...
}

string Program::ReadCommand() {
    string s;
    getline(cin, s);
    return s;
}

void Program::Init() {

}

void Program::Loop() {
    Init();
    while(1) {
        string text = ReadCommand();
        CommandInterpreter commandInterpreter(text);
        // ...
    }
}
