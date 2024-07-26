#include "instructions.h"

void Instructions::add(unsigned char byte) {
    bytes.push_back(byte);
    size++;
}

void Instructions::removeLast() {
    bytes.pop_back();
    size--;
}