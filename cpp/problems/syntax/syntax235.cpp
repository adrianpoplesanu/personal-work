#include <iostream>

void test(int a) {
    std::cout << a << "\n";
}

int main(int argc, char *argv[]) {
    typedef void(*Method)(int);
    Method a = test;
    a(5);
    return 0;
}
