#ifndef __RUNNER_H
#define __RUNNER_H

#include <iostream>

class Runner {
    private:
    std::string name;
    int index;
    public:
    std::string getName();
    void setName(std::string);
    int getIndex();
    void setIndex(int index);
};

#endif