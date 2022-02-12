#include <iostream>

typedef int (*func)(int, int);

int add(int a, int b) {
    return a + b;
}

int addMod10(int a, int b) {
    return (a + b) % 10;
}

int main(int argc, char *argv[]) {
    func a;

    a = &add;
    std::cout << a(11, 12) << "\n";

    a = &addMod10;
    std::cout << a(11, 12) << "\n";

    return 0;
}
