#include "objects.h"

#include <iostream>

std::string Ad_Object::Inspect() {
    return "Inspect() not implemented in subblass";
}

ObjectType Ad_Object::Type() {
    return OT_NULL;
}

void Ad_Object::Print() {
    std::cout << "Print() not implemented in subclass";
}

Ad_String_Object::Ad_String_Object() {
    type = OT_STRING;
}

Ad_String_Object::Ad_String_Object(std::string val) {
    type = OT_STRING;
    value = val;
}

std::string Ad_String_Object::Inspect() {
    return value;
}

ObjectType Ad_String_Object::Type() {
    return type;
}

void Ad_String_Object::Print() {
    std::cout << value;
}
