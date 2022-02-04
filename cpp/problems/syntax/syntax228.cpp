#include <iostream>

int main(int argc, char *argv[]) {
    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < i; j++) {
            std::cout << "*";
        }
        std::cout << "\n";
    }
    return 0;
}
