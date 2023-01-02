#include "objects.h"

std::string Object::inspect() {
    return "UNIMPLEMENTED in";
}

IntegerObject::IntegerObject() {

}

std::string IntegerObject::inspect() {
    return std::to_string(value);
}