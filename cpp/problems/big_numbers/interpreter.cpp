#include <iostream>
#include <string>
#include <map>
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
        for(auto variable : variables) {
            //cout << variable[0] << ":" << variable[1] << endl;
            cout << "showing a variable" << endl;
        }
        return;
    }
    cout << "running...  \r";
    end = clock();
    cout << "ran for " << double(end - start) / CLOCKS_PER_SEC << "secs" << endl;
}
