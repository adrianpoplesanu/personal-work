#ifndef __BRAINFUCK_H
#define __BRAINFUCK_H

#include <iostream>
#include <map>
#include <vector>

enum CommandType {
    UNKNOWN,
    MOVE_RIGHT,
    MOVE_LEFT,
    INCREMENT,
    DECREMENT,
    PRINT,
    READ,
    JUMP_FORWARD,
    JUMP_BACKWARD
};

struct Command {
    Command() : matchingBracket(-1) {
    }
    CommandType type;
    int matchingBracket;
};

class Brainfuck {
public:
    std::string source;
    std::map<char, CommandType> commandsMap;
    std::vector<Command> commands;

    Brainfuck();
    void load(std::string);
    void parse();
    void execute();
};

#endif
