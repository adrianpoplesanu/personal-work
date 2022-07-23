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