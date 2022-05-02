#include "big_number.h"

BigNumber::BigNumber() {
    NUMBER_BASE = 10000;
    DIGIT_SIZE = 4;
    size = 0;
}

BigNumber::~BigNumber() {

}

std::string BigNumber::inspect() {
    return "todo: implement this";
}

void BigNumber::load(std::string source) {
    int start = source.length() - DIGIT_SIZE, end = source.length();
    int i = 0;
    while(end > 0) {
        if (start < 0) start = 0;
        std::string digit = source.substr(start, end - start);
        digits[i] = stoi(digit);
        end -= DIGIT_SIZE;
        start -= DIGIT_SIZE;
        i++;
    }
    size = i;
    while ( i < 100) digits[i++] = 0; // w/o this, the memory address value pointed to is not 0
}

BigNumber BigNumber::operator+(const BigNumber& other) {
    // https://www.programiz.com/cpp-programming/operator-overloading
    BigNumber result;

    int remainder = 0;
    for (int i = 0; i < 100; i++) {
        result.digits[i] = digits[i] + other.digits[i] + remainder;
        remainder = 0;
        while (result.digits[i] >= NUMBER_BASE) {
            result.digits[i] -= NUMBER_BASE;
            remainder++;
        }
        if (result.digits[i] != 0) {
            result.size = i + 1;
        }
    }

    return result;
}

void BigNumber::print() {
    /*for (int i = 0; i < size; i++) {
        std::cout << "digit" << i << ": " << digits[i] << "\n";
    }*/
    std::string result = "";
    for (int i = size - 1; i >= 0; i--) {
        std::string digit = std::to_string(digits[i]);
        if (i == size - 1) {
            result += digit;
        } else {
            unsigned int number_of_zeros = DIGIT_SIZE - digit.length(); // add 4 zeros
            digit.insert(0, number_of_zeros, '0');
            result += digit;
        }
    }
    std::cout << result << "\n";
}