#ifndef __BIG_NUMBER_H
#define __BIG_NUMBER_H

#include <iostream>

class BigNumber {
    public:
        int digits[100];
        int float_digits[100];
        int NUMBER_BASE = 10000;

        std::string inspect();
};

#endif