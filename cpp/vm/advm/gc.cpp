#include "gc.h"

GarbageCollector::GarbageCollector() {
    head = tail = NULL;
}

void GarbageCollector::addObject(AdObject *obj) {
    // TODO: implement this
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
    // TODO: implement this
}