#ifndef __EVAVM_H
#define __EVAVM_H

#include <iostream>
#include <string>
#include <vector>

#include "bytecode/OpCode.h"

#define READ_BYTE() *ip++

class EvaVM {
public:
    EvaVM() {}

    void exec(const std::string &progrm) {
        code = {OP_HALT};

        ip = &code[0];

        return eval();
    }

    void eval() {
        for (;;) {
            switch(READ_BYTE()) {
                case OP_HALT:
                    return;
            }
        }
    }

    uint8_t *ip;
    std::vector<uint8_t> code;
};

#endif