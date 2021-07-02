#include <iostream>

void test(int a) {
    std::cout << a << "\n";
}

void test2(int a) {
    std::cout << a + 2 << "\n";
}

int main(int argc, char *argv[]) {
    void (*fn)(int);

    fn = &test;
    fn(2);

    fn = &test2;
    fn(3);

    return 0;
}
