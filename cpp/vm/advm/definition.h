#ifndef __DEFINITION_H
#define __DEFINITION_H

#include<iostream>

class Definition {
public:
    std::string name;
    int *operandWidths;

    Definition(std::string, int*);
    ~Definition();
};

#endif