#ifndef __BIG_NUMBER_H
#define __BIG_NUMBER_H

#include <iostream>

class BigNumber {
    public:
        int digits[100];
        int float_digits[100];
        int size;
        int NUMBER_BASE;
        int DIGIT_SIZE;

        BigNumber();
        ~BigNumber();
        std::string inspect();
        void load(std::string);
        BigNumber operator + (const BigNumber&);
        bool operator > (const BigNumber&);
        bool operator < (const BigNumber&);
        bool operator >= (const BigNumber&);
        bool operator <= (const BigNumber&);
        void print();
};

#endif