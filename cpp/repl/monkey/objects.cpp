#include "objects.h"
#include <string>

namespace objects {
    Object::Object() {
        type = NULL_OBJ;
    }

    Object::~Object() {

    }

    NullObject::NullObject() {
        type = NULL_OBJ;
    }

    IntObject::IntObject() {
        type = INT_OBJ;
        val = 0;
    }

    IntObject::IntObject(int i) {
        type = INT_OBJ;
        val = i;
    }

    StringObject::StringObject() {
        type = STRING_OBJ;
        val = "";
    }

    StringObject::StringObject(std::string s) {
        type = STRING_OBJ;
        val = s;
    }
}