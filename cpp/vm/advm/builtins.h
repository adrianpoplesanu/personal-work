#ifndef __BUILTINS_H
#define __BUILTINS_H

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
AdObject* print_builtin(std::vector<AdObject*>, GarbageCollector*);
AdObject* println_builtin(std::vector<AdObject*>, GarbageCollector*);

std::vector<Builtin> builtins = {
    Builtin("len", len_builtin),
    Builtin("print", print_builtin),
    Builtin("println", println_builtin)
};

void finalize_free_all_builtin_objects();

#endif