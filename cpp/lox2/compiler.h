#ifndef LOX2_COMPILER_H
#define LOX2_COMPILER_H

#include "object.h"
#include "vm.h"

bool compile(const char* source, Chunk* chunk);

#endif
