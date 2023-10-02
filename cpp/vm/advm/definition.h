#ifndef __DEFINITION_H
#define __DEFINITION_H

#include<iostream>

class Definition {
public:
    std::string name;
    int size;
    int *operandWidths;

    Definition(std::string, int, int*);
    ~Definition();
};

#endif