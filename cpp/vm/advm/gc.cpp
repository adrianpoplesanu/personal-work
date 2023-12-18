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
}

void GarbageCollector::markObject(AdObject* obj) {
    if (obj->marked) return;
    switch(obj->type) {
        case OT_INT: {
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
}

void GarbageCollector::forceFreeObjects() {
    AdObject *current = head;
    while (current != NULL) {
        AdObject *target = current;
        current = current->next;
        free_memory_AdObject(target);
    }
}