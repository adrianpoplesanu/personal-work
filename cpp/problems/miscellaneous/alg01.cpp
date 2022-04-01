#include <iostream>

int main(int argc, char *argv[]) {
    int n = 50, suma = 0;
    for (int i = 2; i < n; i++) {
        bool prim = true;
        for (int j = 2; j < i; j++) if (i % j == 0) prim = false;
        if (prim) {
            std::cout << i << "\n";
            suma += i;
        }
    }
    std::cout << suma << "\n";
    return 0;
}
