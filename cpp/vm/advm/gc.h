#ifndef __GC_H
#define __GC_H

#include "objects.h"

class GarbageCollector {
    AdObject *head;
    AdObject *tail;

public:
    GarbageCollector();

    void addObject(AdObject*);
    void markObjects();
    void markObject(AdObject*);
    void unmarkAllObjects();
    void sweepObjects();
    void forceFreeObjects();
};

#endif