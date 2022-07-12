#include "repl.h"
#include <iostream>

void Repl::loop() {
    while(1) {
        std::string line;
        std::cout << ">> ";
        getline(std::cin, line);
        if (line == "exit()") break;
        parser.load(line);
        parser.buildProgramStatement(program);
    }
}