#ifndef __FRAME_H
#define __FRAME_H

#include "objects.h"

class Frame {
public:
    AdClosureObject* cl = nullptr;
    int ip;
    int basePointer;

    Frame(AdClosureObject*, int);
    Frame(AdClosureObject*, int, int);
    ~Frame();
    Instructions instructions();
};

Frame* newFrame(AdClosureObject*, int);

#endif