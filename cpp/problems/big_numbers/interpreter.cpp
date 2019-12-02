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

CommandInterpreter::~CommandInterpreter() {

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
        regex assign_scalar("^[ ]*([a-zA-Z]+[a-zA-Z0-9]*)[ ]*:[ ]*([0-9]+)[ ]*$");
        smatch m;
        if (regex_search(text, m, assign_scalar)) {
            command_type = ASSIGN_SCALAR;
            return;
        }
        regex assign_variable("^[ ]*([a-zA-Z]+[a-zA-Z0-9]*)[ ]*:[ ]*([a-zA-Z]+[a-zA-Z0-9]*)[ ]*$");
        if (regex_search(text, m, assign_variable)) {
            command_type = VARIABLE_ASSIGN;
            return;
        }
        regex add_in_variable("^[ ]*([a-zA-Z]+[a-zA-Z0-9]*)[ ]*:[ ]*([0-9a-zA-Z]+[ ]*\\+[ ]*[0-9a-zA-Z]+)[ ]*$");
        if (regex_search(text, m, add_in_variable)) {
            command_type = ADD_INVARIABLE_INSTRUCTION;
            return;
        }
        regex normal_add("^[ ]*([0-9a-zA-Z]+)[ ]*\\+[ ]*([0-9a-zA-Z]+)[ ]*$");
        if (regex_search(text, m, normal_add)) {
            command_type = ADD_NORMAL_INSTRUCTION;
            return;
        }
        regex for_instruction("^[ ]*for[ ]*([0-9a-zA-Z]+)[ ]*:[ ]*([0-9a-zA-Z]+)[ ]*:[ ]*([0-9a-zA-Z]+)[ ]*:[ ]*([0-9a-zA-Z]+)[ ]*(.*)$");
        if (regex_search(text, m, for_instruction)) {
            command_type = FOR_INSTRUCTION;
            return;
        }
    }
}

void CommandInterpreter::Execute(map<string, BigNumber> &variables) {
    BigNumber result;
    bool show_result = false;
    if (command_type == EMPTY) {
        // do nothing
        return;
    }
    if (command_type == SHOWALL) {
        if (variables.begin() == variables.end()) {
            cout << "no current variables" << endl;
        } else {
            for (map<string, BigNumber>::iterator it = variables.begin(); it != variables.end(); ++it) {
                cout << it->first << " : ";
                it->second.PrintNumber();
                cout << endl;
            }
        }
        return;
    }
    if (command_type == ASSIGN_SCALAR) {
       regex assign_scalar("^[ ]*([a-zA-Z]+[a-zA-Z0-9]*)[ ]*:[ ]*([0-9]+)[ ]*$");
       smatch m;
       regex_search(text, m, assign_scalar);
       string var_name = m[1];
       string scalar = m[2];
       map<string, BigNumber>::iterator it = variables.find(var_name);
       if (it != variables.end()) {
           BigNumber new_value;
           new_value.LoadFromString(scalar);
           it->second = new_value;
       } else {
           BigNumber number;
           number.LoadFromString(scalar);
           variables.insert(pair<string, BigNumber>(var_name, number));
       }
    }
    if (command_type == VARIABLE_ASSIGN) {
        regex assign_variable("^[ ]*([a-zA-Z]+[a-zA-Z0-9]*)[ ]*:[ ]*([a-zA-Z]+[a-zA-Z0-9]*)[ ]*$");
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
    if (command_type == ADD_INVARIABLE_INSTRUCTION) {
        string dest_var, add_sequence;
        regex add_in_variable("^[ ]*([a-zA-Z]+[a-zA-Z0-9]*)[ ]*:[ ]*([0-9a-zA-Z]+[ ]*\\+[ ]*[0-9a-zA-Z]+)[ ]*$");
        smatch m;
        regex_search(text, m, add_in_variable);
        dest_var = m[1];
        add_sequence = m[2];
        AddNormalInstruction(variables, add_sequence, show_result, result);
        if (show_result) {
            if (CheckVariableExists(variables, dest_var)) {
                SetVariable(variables, dest_var, result);
            } else {
                AddVariable(variables, dest_var, result);
            }
        }
        show_result = false;
    }
    if (command_type == ADD_NORMAL_INSTRUCTION) {
        AddNormalInstruction(variables, text, show_result, result);
    }
    cout << "running...  \r";
    end = clock();
    cout << "ran for " << double(end - start) / CLOCKS_PER_SEC << "secs" << endl;
    if (show_result) result.PrintLineNumber();
}

bool isNumber(string text) {
    regex is_number("^([0-9]+)$");
    smatch m;
    return regex_search(text, m, is_number);
}

bool isVariable(string text) {
    regex is_variable("^([a-zA-Z]+[0-9a-zA-Z]*)$");
    smatch m;
    return regex_search(text, m, is_variable);
}

void AddNumber(BigNumber &desc, BigNumber origin) {

}

bool CheckVariableExists(map<string, BigNumber> variables, string text) {
    // check if variable already exists
    map<string, BigNumber>::iterator it = variables.find(text);
    return it != variables.end();
}

BigNumber GetVariable(map<string, BigNumber> variables, string name) {
    map<string, BigNumber>::iterator it = variables.find(name);
    return it->second;
}

void SetVariable(map<string, BigNumber> &variables, string name, BigNumber value) {
    map<string, BigNumber>::iterator it = variables.find(name);
    it->second = value;
}

void AddVariable(map<string, BigNumber> &variables, string name, BigNumber value) {
    variables.insert(pair<string, BigNumber>(name, value));
}

void AddNormalInstruction(map<string, BigNumber> variables, string text, bool &show_result, BigNumber &result) {
    string membr1, membr2;
    regex normal_add("^[ ]*([0-9a-zA-Z]+)[ ]*\\+[ ]*([0-9a-zA-Z]+)[ ]*$");
    smatch m;
    regex_search(text, m, normal_add);
    membr1 = m[1];
    membr2 = m[2];
    if (isNumber(membr1)) {
        BigNumber numar;
        numar.LoadFromString(membr1);
        result = result + numar;
    } else {
        if (isVariable(membr1)) {
            if (CheckVariableExists(variables, membr1)) {
                BigNumber numar = GetVariable(variables, membr1);
                result = result + numar;
            } else {
                cout << "error - variable " << membr1 << " not defined" << endl;
                return;
            }
        }
    }
    if (isNumber(membr2)) {
        BigNumber numar;
        numar.LoadFromString(membr2);
        result = result + numar;
    } else {
        if (isVariable(membr2)) {
            if (CheckVariableExists(variables, membr2)) {
                BigNumber numar = GetVariable(variables, membr2);
                result = result + numar;
            } else {
                cout << "error - variable " << membr2 << " not defined" << endl;
                return;
            }
        }
    }
    show_result = true;
}