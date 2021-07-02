#include <iostream>

typedef void (*callback)(int);

void test(int a) {
    std::cout << a << "\n";
}

void test2(int a) {
    std::cout << a + 2 << "\n";
}

void test3(callback c, int a) {
    c(a);
}

int main(int argc, char *argv[]) {
    test3(&test, 2);
    test3(&test2, 3);
    return 0;
}
