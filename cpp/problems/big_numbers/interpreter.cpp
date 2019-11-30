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
        regex assign_scalar("^([a-zA-Z]+[a-zA-Z0-9]*):([0-9]+)$");
        smatch m;
        if (regex_search(text, m, assign_scalar)) {
            command_type = ASSIGN_SCALAR;
            return;
        }
        regex assign_variable("^([a-zA-Z]+[a-zA-Z0-9]*):([a-zA-Z]+[a-zA-Z0-9]*)$");
        if (regex_search(text, m, assign_variable)) {
            command_type = VARIABLE_ASSIGN; 
            return;
        }
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
    if (command_type == ASSIGN_SCALAR) {
       regex assign_scalar("^([a-zA-Z]+[a-zA-Z0-9]*):([0-9]+)$");
       smatch m;
       regex_search(text, m, assign_scalar);
       string var_name = m[1];
       string scalar = m[2];
       map<string, BigNumber>::iterator it = variables.find(var_name);
       if (it != variables.end()) {
           it->second.LoadFromString(scalar);
       } else {
           BigNumber number;
           number.LoadFromString(scalar);
           variables.insert(pair<string, BigNumber>(var_name, number));
       }
    }
    if (command_type == VARIABLE_ASSIGN) {
        regex assign_variable("^([a-zA-Z]+[a-zA-Z0-9]*):([a-zA-Z]+[a-zA-Z0-9]*)$");
        smatch m;
        regex_search(text, m, assign_variable);
        string desc_var = m[1];
        string srce_var = m[2];
        map<string, BigNumber>::iterator it = variables.find(srce_var);
        map<string, BigNumber>::iterator it2 = variables.find(desc_var);
        if (it != variables.end()) {
            if (it2 != variables.end()) {
                it2->second = it->second;
            } else {
                variables.insert(pair<string, BigNumber>(desc_var, it->second));
            }
        } else {
            cout << "error - variable " << srce_var << " not defined" << endl;
            return;
        }
    }
    cout << "running...  \r";
    end = clock();
    cout << "ran for " << double(end - start) / CLOCKS_PER_SEC << "secs" << endl;
}
