#include <iostream>

int main(int argc, char *argv[]) {
    int i, a;
    for (i = 0; i < 10; i++) {
        a = i;
        std::cout << i << "\n";
    }
    std::cout << i << "\n";
    std::cout << a << "\n";
    return 0;
}
