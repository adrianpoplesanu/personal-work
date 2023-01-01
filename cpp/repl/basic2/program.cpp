#include "program.h"

Program::Program() {

}

void Program::loop() {
    while(true) {
        std::string line;
        std::cout << ">> ";
        std::cin >> line;
        if (line == "exit") break;
        parser.load(line);
        ASTProgram program;
        parser.parseProgram(program);
    }
}
