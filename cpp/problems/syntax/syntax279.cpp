#include <iostream>

void test2() {
    std::cout << "test2\n";
}

void test1() {
    std::cout << "test1\n";
    test2();
}

int main(int argc, char *argv[]) {
    test1();
    return 0;
}
