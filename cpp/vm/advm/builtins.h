#ifndef __BUILTIN_H
#define __BUILTIN_H

#include "objects.h"
#include "gc.h"
#include <map>

class Builtin {
public:
    typedef AdObject* (*BuiltinFunction)(std::vector<AdObject*>, GarbageCollector*);

    std::string name;
    BuiltinFunction builtin_function;
    AdObjectBuiltin *builtin_object;
    Builtin(std::string, BuiltinFunction);
};

AdObject* len_builtin(std::vector<AdObject*>, GarbageCollector*);

#endif