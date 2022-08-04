#include "environment.h"

Environment* newEnvironment() {
    Environment* env = new Environment();
    return env;
}

Environment* newEnvironmentWithOuter(Environment* outer) {
    Environment* env = new Environment();
    env->outer = outer;
    return env;
}

AdObject* Environment::get(std::string key) {
    if (store.find(key) != store.end()) {
        return store.at(key);
    }
    if (outer->store.find(key) != outer->store.end()) {
        return outer->store.at(key);
    }
    return NULL;
}

void Environment::save(std::string key, AdObject* obj) {
    
}