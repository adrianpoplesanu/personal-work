#include "objects.h"

std::string AdObject::inspect() {
    return "unimplemented in subclass";
}

std::string AdObject::toString() {
    return "unimplemented in subclass";
}

std::string AdObjectInteger::inspect() {
    return "todo";
}

std::string AdObjectInteger::toString() {
    return "todo";
}

AdObjectInteger::AdObjectInteger() {
    type = OT_INT;
}