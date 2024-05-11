#include "gc.h"

GarbageCollector::GarbageCollector() {
    head = NULL;
    tail = NULL;
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

void GarbageCollector::markObjects(AdObject *stack[2048], int sp) {
    // idea: mark all objects left on the stack
    for (int i = 0; i < sp; i++) {
        markObject(stack[i]);
    }
}

void GarbageCollector::markObjects(std::vector<AdObject *> constants) {
    // idea: mark all objects left on constants
    int i = 0;
    while (i < constants.size()) {
        markObject(constants.at(i));
        i++;
    }
}

void GarbageCollector::markObject(AdObject* obj) {
    if (obj == NULL) return;
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
    // idea: delete all objects that are not marked
    AdObject *iter = head;
    while (iter != NULL) {
        AdObject *target = NULL;
        if (!iter->marked) {
            target = iter;
        }
        iter = iter->next;
        if (target != NULL) {
            sweepObject(target);
        }
    }
}

void GarbageCollector::sweepObject(AdObject* target) {
    if (target == head && target == tail) {
        head = NULL;
        tail = NULL;
    } else if (target == head) {
        head = target->next;
        head->prev = NULL;
    } else if (target == tail) {
        tail = target->prev;
        tail->next = NULL;
    } else {
        AdObject* prev = target->prev;
        AdObject* next = target->next;

        prev->next = next;
        next->prev = prev;
    }

    free_memory_AdObject(target);
}

void GarbageCollector::forceFreeObjects() {
    unmarkAllObjects();
    sweepObjects();
}
