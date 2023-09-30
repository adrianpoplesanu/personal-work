#include "repl.h"
#include <iostream>

void Repl::loop() {
    while(1) {
        std::string line;
        std::cout << ">> ";
        getline(std::cin, line);
        if (line == "exit()") break;
        parser.load(line);
        program.reset();
        parser.buildProgramStatement(program);

        compiler.reset();
        compiler.compile(&program); // TODO: program should be a pointer
        Bytecode bytecode = compiler.getBytecode();
        vm.load(bytecode);
        AdObject* result = vm.last_popped_stack_element();
        if (result != NULL) {
            std::cout << result->inspect() << "\n";
        }
    }
}