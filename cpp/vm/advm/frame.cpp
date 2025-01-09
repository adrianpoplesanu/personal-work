#include "frame.h"

Frame::Frame(AdClosureObject *c, int i) {
    cl = c;
    ip = i;
    basePointer = 0;
}

Frame::Frame(AdClosureObject *c, int i, int bP) {
    cl = c;
    ip = i;
    basePointer = bP;
}

Frame::~Frame() {
    if (cl != NULL) {
        //free_memory_AdObject(cl); // poate ca da, poate ca nu, vedem daca aici e locul de stergere a closure-ului
        // ceva imi spune ca aici trebuie ceva mai complex
    }
}

Instructions Frame::instructions() {
    return cl->fn->instructions;
}

Frame* newFrame(AdClosureObject *cl, int basePointer) {
    return new Frame(cl, -1, basePointer);
}