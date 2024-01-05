#include "repl.h"
#include <iostream>

Repl::Repl() {
    program = new ASTProgram();
    gc = new GarbageCollector();
    compiler.gc = gc;
    vm.gc = gc;
}

Repl::~Repl() {
    gc->forceFreeObjects();
    delete gc;
    delete program;
}

void Repl::loop() {
    while(1) {
        std::string line;
        std::cout << ">> ";
        getline(std::cin, line);
        if (line == "exit()") break;
        parser.load(line);
        program->reset();
        parser.buildProgramStatement(program);

        compiler.reset();
        compiler.compile(program);

        Bytecode bytecode = compiler.getBytecode();
        compiler.code.instructions = bytecode.instructions;
        std::cout << compiler.code.toString(); // asta pare ca functioneaza cum trebuie

        vm.load(bytecode);
        vm.run();

        gc->unmarkAllObjects();
        gc->markObjects(vm.stack, vm.sp);
        gc->sweepObjects();

        AdObject* result = vm.last_popped_stack_element();
        if (result != NULL) {
            std::cout << result->inspect() << "\n";
        }
    }
}