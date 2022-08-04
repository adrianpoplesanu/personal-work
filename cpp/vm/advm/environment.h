#ifndef __ENVIRONMENT_H
#define __ENVIRONMENT_H

#include "objects.h"
#include <map>

class Environment {
public:
    std::map<std::string, AdObject*> store;
    Environment* outer;

    Environment();
    AdObject* get(std::string);
    void save(std::string, AdObject*);
};

Environment* newEnvironment();
Environment* newEnvironmentWithOuter(Environment*);

#endif