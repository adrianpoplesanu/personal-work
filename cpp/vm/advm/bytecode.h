#ifndef __BYTECODE_H
#define __BYTECODE_H

#include "instructions.h"
#include "objects.h"

class Bytecode {
    Instructions instructions;
    std::vector<AdObject*> constants;
};

#endif