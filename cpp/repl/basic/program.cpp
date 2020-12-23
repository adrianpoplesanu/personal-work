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
        else if (command == "LIST") {
            for (vector<string>::iterator it = commands.begin(); it != commands.end(); ++it) {
                cout << *it << '\n';
            }
        } 
        else if (command == "EXIT") {
            break;
        } 
        else if (command == "RUN") {
            cout << "running the program..." << '\n';
        } else {
            commands.push_back(command);
        }
    }
}
