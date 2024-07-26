#ifndef __INSTRUCTIONS_H
#define __INSTRUCTIONS_H

#include <vector>

class Instructions {
public:
    int size;
    std::vector<unsigned char> bytes;
    void add(unsigned char);
    void removeLast();
};

#endif