#include "code.h"

Code::Code() {
    definitionsMap.insert(std::make_pair(OP_CONSTANT, new Definition("OpConstant", new int[1] {2})));
    definitionsMap.insert(std::make_pair(OP_ADD, new Definition("OpAdd", new int)));
}

Code::~Code() {
    for(std::map<unsigned char, Definition*>::iterator it = definitionsMap.begin(); it != definitionsMap.end(); it++) {
        delete it->second;
    }
}

unsigned char* Code::make(OpCode opCode, int n, std::list<int> &args) {
    return NULL;
}