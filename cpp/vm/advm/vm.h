#ifndef __VM_H
#define __VM_H

#include "objects.h"
#include "bytecode.h"

class VM {
public:
    void load(Bytecode);
    AdObject* last_popped_stack_element();
};

#endif