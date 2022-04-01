#include <iostream>

bool prim(int n) {
    for (int i = 2; i < n / 2; i++) if (n % i == 0) return false;
    return true;
}

int main(int argc, char *argv[]) {
    int n = 48;
    for (int i = 2; i < n / 2; i++) {
        int a = i, b = n - i;
        if (prim(a) && prim(b)) {
            std::cout << a << " " << b << "\n";
        }
    }
    return 0;
}
