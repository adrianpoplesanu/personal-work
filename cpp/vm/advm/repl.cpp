#include "repl.h"
#include <iostream>

Repl::Repl() {
    gc = new GarbageCollector();
    compiler.gc = gc;
    vm.setGarbageCollector(gc);
}

Repl::~Repl() {
    gc->forceFreeObjects();
    delete gc;
}

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
        compiler.code.instructions = bytecode.instructions;
        std::cout << compiler.code.toString(); // asta pare ca functioneaza cum trebuie
        vm.load(bytecode);
        vm.run();
        AdObject* result = vm.last_popped_stack_element();
        if (result != NULL) {
            std::cout << result->inspect() << "\n";
        }
    }
}