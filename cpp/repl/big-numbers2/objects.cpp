#include "objects.h"

void BN_INCREF(BNObject* obj) {
    if (obj) {
        obj->ref_count++;
    }
}

void BN_DECREF(BNObject* obj) {
    if (obj) {
        obj->ref_count--;
    }
}

void free_BN_object_memory(BNObject* obj) {
    if (!obj) return;
    if (obj->ref_count > 0) return;
    switch(obj->type) {
        default:
            std::cout << "MEMORY ERROR: unknown object deallocation for: " << object_type_converter[obj->type] << "\n";
        break;
    }
}