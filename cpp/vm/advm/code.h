#ifndef __CODE_H
#define __CODE_H

#include "opcode.h"
#include "definition.h"
#include <list>
#include <map>

class Code {
public:
    std::map<unsigned char, Definition*> definitionsMap;

    Code();
    ~Code();
    unsigned char* make(OpCode opCode, int n, std::list<int>&);
};

#endif