#include <iostream>

// cppcon lambdas series

int plus1(int x) {
    return x + 1;
}

int main(int argc, char *argv[]) {
    int a = 5;
    std::cout << plus1(a) << "\n";
    return 0;
}
