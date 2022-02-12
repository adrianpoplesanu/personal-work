#include <iostream>

int add(int a, int b) {
    return a + b;
}

int addMod10(int a, int b) {
    return (a + b) % 10;
}

int main(int argc, char* argv[]) {
    int (*func)(int, int);

    func = &add;

    std::cout << func(11, 12) << "\n";

    func = &addMod10;

    std::cout << func(11, 12) << "\n";

    return 0;
}
