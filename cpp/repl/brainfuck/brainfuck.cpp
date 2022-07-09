#include "brainfuck.h"

Brainfuck::Brainfuck() {
    commandsMap['>'] = MOVE_RIGHT;
}

void Brainfuck::load(std::string s) {
    source = s;
}

void Brainfuck::parse() {
    std::vector<int> bracketsStack;
    int i = 0;
    while(i < source.size()) {
        std::map<char, CommandType>::iterator found = commandsMap.find(source[i]);
        if (found != commandsMap.end()) {
            Command command;
            command.type = found->second;
            if (command.type == JUMP_FORWARD) {
                bracketsStack.push_back(commands.size());
            }
            if (command.type == JUMP_BACKWARD) {
                int matching_bracket = bracketsStack.back();
                bracketsStack.pop_back();
                command.matchingBracket = matching_bracket;
                commands[matching_bracket].matchingBracket = commands.size();
            }
            commands.push_back(command);
        } else {
            Command command;
            command.type = UNKNOWN;
            commands.push_back(command);
        }
        i++;
    }
}

void Brainfuck::execute() {
    int i = 0;
    while (i < commands.size()) {
        std::cout << commands[i].type << "\n";
        i++;
    }
}
