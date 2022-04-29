#include <iostream>

int main(int argc, char *argv[]) {
    int a;
    int *b = new int(5);

    std::cout << &a << "\n" << b << "\n" << &b << "\n";
    return 0;
}
