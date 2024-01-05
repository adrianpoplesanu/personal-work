#include "gc.h"

GarbageCollector::GarbageCollector() {
    head = tail = NULL;
}

void GarbageCollector::addObject(AdObject *obj) {
    if (head == NULL && tail == NULL) {
        head = tail = obj;
    } else {
        obj->next = NULL;
        obj->prev = tail;
        tail->next = obj;
        tail = obj;
    }
}

void GarbageCollector::markObjects() {
    // TODO: implement this
    // idea: mark all objects left on the stack
}

void GarbageCollector::markObject(AdObject* obj) {
    if (obj->marked) return;
    switch(obj->type) {
        case OT_INT: {
            obj->marked = true;
            break;
        }
        default: {
            std::cout << "MEMORY ERROR!!! garbage collection inconsistency!\n";
            break;
        }
    }
    obj->marked = true;
}

void GarbageCollector::unmarkAllObjects() {
    AdObject *iter = head;
    while (iter != NULL) {
        iter->marked = false;
        iter = iter->next;
    }
}

void GarbageCollector::sweepObjects() {
    // TODO: implement this
    // idea: delete all objects that are not marked
}

void GarbageCollector::forceFreeObject(AdObject* obj) {
    AdObject* prev = obj->prev;
    AdObject* next = obj->next;

    if (prev) {
        prev->next = next;
    }
    if (next) {
        next->prev = prev;
    }

    free_memory_AdObject(obj);
}

void GarbageCollector::forceFreeObjects() {
    AdObject *current = head;
    while (current != NULL) {
        AdObject *target = current;
        current = current->next;
        free_memory_AdObject(target);
    }
}
