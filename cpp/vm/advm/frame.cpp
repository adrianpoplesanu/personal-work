#include "frame.h"

Frame::Frame(AdObjectCompiledFunction *f, int i) {
    fn = f;
    ip = i;
    basePointer = 0;
}

Frame::Frame(AdObjectCompiledFunction *f, int i, int bP) {
    fn = f;
    ip = i;
    basePointer = bP;
}

Frame::~Frame() {
    if (fn != NULL) {
        free_memory_AdObject(fn); // poate ca da, poate ca nu, vedem daca aici e locul de stergere a compiled function-ului
    }
}

Instructions Frame::instructions() {
    return fn->instructions;
}

Frame* newFrame(AdObjectCompiledFunction *fn, int basePointer) {
    return new Frame(fn, -1, basePointer);
}