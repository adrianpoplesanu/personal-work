#include <iostream>

int main(int argc, char* argv[]) {
    int n = 20;
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            std::cout << ".";
        }
    }
    std::cout << "\nO(^2)\n";
    return 0;
}
