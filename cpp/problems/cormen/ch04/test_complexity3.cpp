#include <iostream>

int main(int argc, char* argv[]) {
    int n = 20;
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            for (int k = i; k <= j; k++) {
                std::cout << ".";
            }
        }
    }
    std::cout << "\nO(n^3)\n";
    return 0;
}
