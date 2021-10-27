#include <iostream>

typedef int(*Callback)();

int test() {
    return 747;
}

int main(int argc, char *argv[]) {
    Callback callback = &test;

    std::cout << callback() << '\n';

    return 0;
}
