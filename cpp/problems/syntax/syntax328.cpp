#include <iostream>

int plus1(int x) {
    return x + 1;
}

double plus1(double x) {
    return x + 1;
}

int main(int argc, char *argv[]) {
    int a = 5;
    std::cout << plus1(a) << "\n";

    double b = 7;
    std::cout << plus1(b) << "\n";
    return 0;
}
