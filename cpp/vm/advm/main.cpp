#include <iostream>

#include "ast.h"
#include "ast.cpp"
#include "code.h"
#include "code.cpp"
#include "compiler.h"
#include "compiler.cpp"
#include "evaluator.h"
#include "evaluator.cpp"
#include "lexer.h"
#include "lexer.cpp"
#include "objects.h"
#include "objects.cpp"
#include "parser.h"
#include "parser.cpp"
#include "repl.h"
#include "repl.cpp"
#include "token.h"
#include "token.cpp"
#include "vm.h"
#include "vm.cpp"

int main(int argc, char* argv[]) {
    std::cout << "testing a simple VM\n";
    Repl repl;
    repl.loop();
    return 0;
}
