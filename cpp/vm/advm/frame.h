#ifndef __FRAME_H
#define __FRAME_H

#include "objects.h"

class Frame {
public:
    AdObjectCompiledFunction* fn;
    int ip;

    Frame(AdObjectCompiledFunction*, int);
    ~Frame();
    Instructions instructions();
};

Frame* newFrame(AdObjectCompiledFunction*);

#endif