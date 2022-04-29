#include "big_number.h"

BigNumber::BigNumber() {
    NUMBER_BASE = 10000;
    size = 0;
}

BigNumber::~BigNumber() {

}

std::string BigNumber::inspect() {
    return "todo: implement this";
}

void BigNumber::load(std::string source) {
    int start = source.length() - 4, end = source.length();
    int i = 0;
    while(end > 0) {
        if (start < 0) start = 0;
        std::string digit = source.substr(start, end - start);
        digits[i] = stoi(digit);
        end -= 4;
        start -= 4;
        i++;
    }
    size = i;
}

BigNumber& BigNumber::operator+(const BigNumber& other) {
    return *this;
}

void BigNumber::print() {
    for (int i = 0; i < size; i++) {
        std::cout << "digit" << i << ": " << digits[i] << "\n";
    }
}