#include "test.h"
#include "ast.h"
#include "gc.h"
#include "compiler.h"
#include "opcode.h"

void run_code_make_test1() {
    Code code;
    std::vector<int> args;
    args.push_back(65534);
    int size = 0;
    OpConstant opConstant = OpConstant();
    unsigned char* instructions;
    instructions = code.make(opConstant, 1, args, size);
    std::cout << (int)instructions[0] << " " << (int)instructions[1] << " " << (int)instructions[2] << "\n";
}

void run_code_make_test2() {
    Code code;
    std::vector<int> args;
    args.push_back(0);
    int size = 0;
    OpConstant opConstant = OpConstant();
    unsigned char* instructions;
    instructions = code.make(opConstant, 1, args, size);
    std::cout << (int)instructions[0] << " " << (int)instructions[1] << " " << (int)instructions[2] << "\n";
}

void run_tests() {
    std::cout << "running tests...\n";
    run_code_make_test1();
    run_code_make_test2();
}