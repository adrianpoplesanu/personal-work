#include "objects.h"

std::string AdObject::inspect() {
    return "unimplemented in subclass";
}

std::string AdObject::toString() {
    return "unimplemented in subclass";
}

AdObjectInteger::AdObjectInteger() {
    type = OT_INT;
}

AdObjectInteger::AdObjectInteger(int v) {
    type = OT_INT;
    value = v;
}

std::string AdObjectInteger::inspect() {
    std::string out = "";
    out = std::to_string(value);
    return out;
}

std::string AdObjectInteger::toString() {
    return "todo";
}

AdObjectBoolean::AdObjectBoolean() {
    type = OT_BOOL;
}

AdObjectBoolean::AdObjectBoolean(bool v) {
    type = OT_BOOL;
    value = v;
}

std::string AdObjectBoolean::inspect() {
    if (value) {
        return "true";
    }
    return "false";
}

std::string AdObjectBoolean::toString() {
    return "todo";
}

void AD_INCREF(AdObject* obj) {
    if (obj != NULL) {
        obj->ref_count++;
    }
}

void AD_DECREF(AdObject* obj) {
    if (obj != NULL) {
        obj->ref_count--;
    }
}

void free_memory_AdObject(AdObject* obj) {
    if (obj == NULL) return;
    switch(obj->type) {
        case OT_INT: {
            delete (AdObjectInteger*) obj;
            break;
        }
        case OT_BOOL: {
            delete (AdObjectBoolean*) obj;
            break;
        }
        default: {
            std::cout << "ERROR: object type not handled\n";
            break;
        }
    }
}