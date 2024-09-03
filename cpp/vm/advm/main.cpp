#include <iostream>
#include <fstream>

#include "ast.h"
#include "ast.cpp"
#include "builtins.h"
#include "builtins.cpp"
#include "bytecode.h"
#include "bytecode.cpp"
#include "code.h"
#include "code.cpp"
#include "compiler.h"
#include "compiler.cpp"
#include "definition.h"
#include "definition.cpp"
#include "environment.h"
#include "environment.cpp"
#include "evaluator.h"
#include "evaluator.cpp"
#include "gc.h"
#include "gc.cpp"
#include "instructions.h"
#include "instructions.cpp"
#include "lexer.h"
#include "lexer.cpp"
#include "objects.h"
#include "objects.cpp"
#include "parser.h"
#include "parser.cpp"
#include "repl.h"
#include "repl.cpp"
#include "test.h"
#include "test.cpp"
#include "token.h"
#include "token.cpp"
#include "vm.h"
#include "vm.cpp"
#include "emitted_instruction.h"
#include "emitted_instruction.cpp"
#include "symbol_table.h"
#include "symbol_table.cpp"

int main(int argc, char* argv[]) {
    if (RUN_TESTS) {
        run_tests();
        return 0;
    }
    Repl repl;
    if (argc == 1) {
        repl.loop();
    } else {
        for (int i = 1; i < argc; i++) {
			std::ifstream target(argv[i]);
			repl.executeFile(target);
		}
    }
    return 0;
}
