#ifndef __EVAVM_H
#define __EVAVM_H

#include <string>
#include <vector>

#include "../bytecode/OpCode.h"

class EvaVM {
public:
    EvaVM() {}

    void exec(const std::string &progrm) {
        ip = &code[0];

        return eval();
    }

    void eval() {
        for (;;) {
            //...
        }
    }

    uint8_t *ip;
    std::vector<uint8_t> code;
};

#endif