#include "program.h"
#include "utils.cpp"

Program::Program() {
    env = new Environment();
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
        //print_AST_node(&program, 0);
        evaluator.eval(&program, env);
    }
}
