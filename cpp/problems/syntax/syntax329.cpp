#include <iostream>

template<typename T>
T plus1(T x) {
    return x + 1;
}

int main(int argc, char *argv[]) {
    int a = 5;
    std::cout << plus1(a) << "\n";

    double b = 7;
    std::cout << plus1(b) << "\n";

    float c = 1.4;
    std::cout << plus1(c) << "\n";
    return 0;
}
