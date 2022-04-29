#include <iostream>
#include "big_number.h"
#include "big_number.cpp"

int main(int argc, char* argv[]) {
    std::cout << "running some tests on the BigNumber class...\n";
    BigNumber number1;
    number1.load("11122223333");
    number1.print();
    return 0;
}