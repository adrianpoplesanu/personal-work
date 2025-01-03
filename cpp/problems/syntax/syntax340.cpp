#include <iostream>

void test() {
    static int a = 0;
    std::cout << a << "\n";
    a++;
}

int main(int argc, char *argv[]) {
    test();
    test();
    test();
    return 0;
}
