#include <iostream>
#include "program.cpp"
#include "lexer.cpp"
#include "parser.cpp"
#include "evaluator.cpp"
#include "ast.cpp"
#include "token.cpp"
#include "objects.cpp"

int main(int argc, char* argv[]) {
    Program program;
    program.loop();
    return 0;
}
