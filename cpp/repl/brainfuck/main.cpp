#include <iostream>
#include "brainfuck.h"
#include "brainfuck.cpp"

int main(int argc, char* argv[]) {
    Brainfuck brainfuck;
    brainfuck.load("++++++++++[>+++++++>++++++++++>+++>+<<<<-]>++.>+.+++++++..+++.>++.<<+++++++++++++++.>.+++.------.--------.>+.>.");
    brainfuck.parse();
    brainfuck.execute();
    return 0;
}
