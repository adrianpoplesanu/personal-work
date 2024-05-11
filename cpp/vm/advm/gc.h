#ifndef __GC_H
#define __GC_H

#include "objects.h"
#include <vector>

class GarbageCollector {
    AdObject *head;
    AdObject *tail;

public:
    GarbageCollector();

    void addObject(AdObject*);
    void markObjects(AdObject *stack[2048], int sp);
    void markObjects(std::vector<AdObject*>);
    void markObject(AdObject*);
    void unmarkAllObjects();
    void sweepObjects();
    void sweepObject(AdObject*);
    void forceFreeObjects();
};

#endif