#include <iostream>

int main(int argc, char *argv[]) {
    float x = 13.78;
    std::cout << x << "\n";
    long y = * (long*) &x;
    std::cout << y << "\n";
    return 0;
}
