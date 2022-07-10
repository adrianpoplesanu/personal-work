#include "brainfuck.h"

Brainfuck::Brainfuck() {
    commandsMap['>'] = MOVE_RIGHT;
    commandsMap['<'] = MOVE_LEFT;
    commandsMap['+'] = INCREMENT;
    commandsMap['-'] = DECREMENT;
    commandsMap['.'] = PRINT;
    commandsMap[','] = READ;
    commandsMap['['] = JUMP_FORWARD;
    commandsMap[']'] = JUMP_BACKWARD;
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
    memset(ptr, 0, 1000);
    cp = 0;
    int i = 0;
    while (i < commands.size()) {
        switch (commands[i].type) {
            case MOVE_RIGHT:
                cp++;
            break;
            case MOVE_LEFT:
                cp--;
            break;
            case INCREMENT:
                ptr[cp]++;
            break;
            case DECREMENT:
                ptr[cp]--;
            break;
            case PRINT:
                std::cout << (char)ptr[cp];
            break;
            case READ:
                std::cin >> ptr[cp];
            break;
            case JUMP_FORWARD:
                if (ptr[cp] == 0) {
                    i = commands[i].matchingBracket;
                }
            break;
            case JUMP_BACKWARD:
                if (ptr[cp] != 0) {
                    i = commands[i].matchingBracket;
                }
            break;
            case UNKNOWN:
                // do nothing
            break;
        }
        i++;
    }
}
