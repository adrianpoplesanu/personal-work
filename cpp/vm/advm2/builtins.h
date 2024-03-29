#ifndef __BUILTIN_H
#define __BUILTIN_H

#include "objects.h"
#include <map>

class Builtins {
public:
    std::map<std::string, AdObject*> store;

    AdObject* get(std::string);
};

#endif