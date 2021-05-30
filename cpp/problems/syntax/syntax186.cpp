#include <iostream>

int test(int n, ...) {
    std::cout << "test()\n";
    return n;
}

int main(int argc, char *argv[]) {
    int (*func)(int n, ...);

    func = &test;

    int res = func(5);
    std::cout << res << "\n";

    return 0;
}
