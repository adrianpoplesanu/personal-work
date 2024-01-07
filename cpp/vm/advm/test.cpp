#include "test.h"
#include "ast.h"
#include "gc.h"
#include "compiler.h"
#include "opcode.h"

void test_code_make_test1() {
    Code code;
    std::vector<int> args;
    args.push_back(65534);
    int size = 0;
    OpConstant opConstant = OpConstant();
    unsigned char* instructions;
    instructions = code.make(opConstant, 1, args, size);
    std::cout << (int)instructions[0] << " " << (int)instructions[1] << " " << (int)instructions[2] << "\n";
    delete[] instructions; // asta e intotdeauna necesar
}

void test_code_make_test2() {
    Code code;
    std::vector<int> args;
    args.push_back(0);
    int size = 0;
    OpConstant opConstant = OpConstant();
    unsigned char* instructions;
    instructions = code.make(opConstant, 1, args, size);
    std::cout << (int)instructions[0] << " " << (int)instructions[1] << " " << (int)instructions[2] << "\n";
    delete[] instructions; // asta e intotdeauna necesar
}

void test_compiler_compilet1() {
    Parser parser;
    Compiler compiler;
    ASTProgram *program = new ASTProgram();
    GarbageCollector *gc = new GarbageCollector();
    compiler.gc = gc;

    parser.load("1+2");
    program->reset();
    parser.buildProgramStatement(program);

    compiler.reset();
    compiler.compile(program);

    Bytecode bytecode = compiler.getBytecode();
    std::cout << bytecode.constants.at(0)->inspect() << " " << bytecode.constants.at(1)->inspect() << "\n";
    for (int i = 0; i < bytecode.instructions.size; i++) {
        std::cout << std::setw(4) << std::setfill('0') << (int)bytecode.instructions.bytes.at(i) << " ";
    }
    std::cout << "\n";

    gc->forceFreeObjects();
    delete gc;
    delete program;
}

void run_tests() {
    std::cout << "running tests...\n";
    test_code_make_test1();
    test_code_make_test2();
    test_compiler_compilet1();
}