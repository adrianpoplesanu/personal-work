#include <iostream>
#include <string>
#include <map>
#include <regex>
#include "interpreter.h"
#include "big_number.h"
using namespace std;

CommandInterpreter::CommandInterpreter() : text("") {
    //...
}

CommandInterpreter::CommandInterpreter(string s) {
    text = s;
}

void CommandInterpreter::Analyze() {
    start = clock();
    if (text == "") {
        command_type = EMPTY;
    } else if (text == "showall") {
        command_type = SHOWALL;
    } else {
        cout << "analyzing...\r";
        command_type = UNKNOWN;
        // do regex checks and determine if this is assign, add, reference or for
    }
}

void CommandInterpreter::Execute(map<string, BigNumber> &variables) {
    if (command_type == EMPTY) {
        // do nothing
        return;
    }
    if (command_type == SHOWALL) {
        if (variables.begin() == variables.end()) {
            cout << "no current variables" << endl;
        } else {
            for (map<string, BigNumber>::iterator it = variables.begin(); it != variables.end(); ++it) {
                cout << it->first << ":";
                it->second.PrintNumber();
                cout << endl;
            }
        }
        return;
    }
    if (command_type == VARIABLE_ASSIGN) {

    }
    cout << "running...  \r";
    end = clock();
    cout << "ran for " << double(end - start) / CLOCKS_PER_SEC << "secs" << endl;
}
