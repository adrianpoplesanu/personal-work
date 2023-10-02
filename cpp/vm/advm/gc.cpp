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

void GarbageCollector::markObject(AdObject*) {
    // TODO: implement this
}

void GarbageCollector::unmarkAllObjects() {
    // TODO: implement this
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