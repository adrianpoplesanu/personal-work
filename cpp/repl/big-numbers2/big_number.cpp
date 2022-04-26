#include "big_number.h"

BigNumber::BigNumber() {
    NUMBER_BASE = 10000;
}

BigNumber::~BigNumber() {

}

std::string BigNumber::inspect() {
    return "todo: implement this";
}

void BigNumber::load(std::string) {

}

BigNumber& BigNumber::operator+(const BigNumber& other) {
    return *this;
}