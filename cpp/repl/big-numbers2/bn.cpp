#include <iostream>
#include <fstream>
#include "big_number.h"
#include "big_number.cpp"
#include "repl.h"
#include "repl.cpp"
#include "parser.h"
#include "parser.cpp"
#include "lexer.h"
#include "lexer.cpp"
#include "ast.h"
#include "ast.cpp"
#include "evaluator.h"
#include "evaluator.cpp"

int main(int argc, char* argv[]) {
    Repl repl;
    if (argc == 1) {
        std::cout << "bn interpreter [C++] - Big Numbers ver2\n";
        repl.Loop();
    } else {
        std::ifstream target(argv[1]);
        repl.ExecuteFile(target);
    }
    return 0;
}
