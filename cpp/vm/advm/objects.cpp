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
    return "todo";
}

std::string AdObjectInteger::toString() {
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
        default: {
            std::cout << "ERROR: object type not handled\n";
            break;
        }
    }
}