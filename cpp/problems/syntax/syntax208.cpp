#include <iostream>

typedef int(*Callback)();

int test() {
    return 747;
}

void test2(Callback *callback) {
    int val = (*callback)();
    std::cout << val << '\n';
}

int main(int argc, char *argv[]) {
    Callback callback = *test;

    std::cout << callback() << '\n';
    test2(&callback);

    return 0;
}
