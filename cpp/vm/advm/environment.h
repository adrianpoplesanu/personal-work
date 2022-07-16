#ifndef __ENVIRONMENT_H
#define __ENVIRONMENT_H

#include "objects.h"
#include <map>

class Environment {
public:
    std::map<std::string, AdObject*> store;
    Environment* outer;

    Environment();
};

Environment* newEnvironment();
Environment* newEnvironmentWithOuter(Environment*);

#endif