#ifndef __FRAME_H
#define __FRAME_H

#include "objects.h"

class Frame {
public:
    AdObjectCompiledFunction* fn = nullptr;
    int ip;
    int basePointer;

    Frame(AdObjectCompiledFunction*, int);
    Frame(AdObjectCompiledFunction*, int, int);
    ~Frame();
    Instructions instructions();
};

Frame* newFrame(AdObjectCompiledFunction*, int);

#endif