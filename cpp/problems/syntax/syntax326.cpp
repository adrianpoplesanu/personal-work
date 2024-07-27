#include <iostream>

enum OpCode {
    OP_CONSTANT,
    OP_JUMP,
    OP_POP
};

int main(int argc, char *argv[]) {
    unsigned char a = 0;

    OpCode op1 = static_cast<OpCode>(a);
    std::cout << op1 << "\n";

    unsigned char b = 1;
    OpCode op2 = static_cast<OpCode>(b);
    std::cout << op2 << "\n";

    return 0;
}
