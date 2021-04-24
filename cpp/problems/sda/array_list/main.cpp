#include <iostream>
#include "listobject.h"
#include "listobject.cpp"

void test() {
    ListObject<int> numbers;
    std::cout << numbers.getSize() << "\n";
    numbers.append(7);
    numbers.append(4);
    numbers.append(7);
    numbers.print();
    std::cout << numbers.getSize() << "\n";
    numbers.print_memory_addresses();
    numbers.append(6);
    numbers.append(8);
    int a = numbers.pop();
    std::cout << a << "\n";
    numbers.print();
    std::cout << numbers.getSize() << "\n";
    numbers.print_memory_addresses();
}

int main(int argc, char *argv[]) {
    std::cout << "buna dimineata!\n";
    test();
    test();
    return 0;
}