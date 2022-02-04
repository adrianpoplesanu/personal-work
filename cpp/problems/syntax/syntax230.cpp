#include <iostream>

int main(int argc, char *argv[]) {
    std::cout << "ascii printer\n";
    for (char c = 0; c < 127; c++) {
        if (c < 10) std::cout << "00";
        else if (c < 100) std::cout << "0";
        std::cout << (int) c << " " << c << '\n';
    }
    return 0;
}
