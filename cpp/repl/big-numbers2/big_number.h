#ifndef __BIG_NUMBER_H
#define __BIG_NUMBER_H

#include <iostream>

class BigNumber {
    public:
        int digits[100];
        int float_digits[100];
        int NUMBER_BASE;

        BigNumber();
        ~BigNumber();
        std::string inspect();
        void load(std::string);
        BigNumber& operator+(const BigNumber&);
};

#endif