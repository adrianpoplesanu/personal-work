#include <iostream>

// using auto as type

template<typename T>
T plus1(T x) {
    return x + 1;
}

int main(int argc, char *argv[]) {
    auto a = plus1(5);
    std::cout << a << "\n";

    auto b = plus1(1.4);
    std::cout << b << "\n";
    return 0;
}
