#include <iostream>

int main(int argc, char *argv[]) {
    int i = 0;
    while (i++ < 5) std::cout << i << " ";
    std::cout << '\n' << i << '\n';
    i = 0;
    while (++i < 5) std::cout << i << " ";
    std::cout << '\n' << i << '\n';
    return 0;
}
