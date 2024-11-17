#include "frame.h"

Frame::Frame(AdObjectCompiledFunction *f, int i) {
    fn = f;
    ip = i;
}

Frame::~Frame() {
    if (fn != NULL) {
        free_memory_AdObject(fn); // poate ca da, poate ca nu, vedem daca aici e locul de stergere a compiled function-ului
    }
}

Instructions Frame::instructions() {
    return fn->instructions;
}

Frame* newFrame(AdObjectCompiledFunction *fn) {
    return new Frame(fn, -1);
}