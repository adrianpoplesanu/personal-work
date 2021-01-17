#include <iostream>
#include <vector>
#include "program.h"
#include "parser.h"
using namespace std;


Program::Program () {
    // ...
}

Program::~Program () {
    // ...
}

void Program::Run () {
    string command;
    vector<string> commands;

    while (1) {
        cout << "> ";
        getline(cin, command);
        if (command == "") continue;
        else if (command == "EXIT") {
            break;
        } else {
            commands.push_back(command);
        }
    }
}
