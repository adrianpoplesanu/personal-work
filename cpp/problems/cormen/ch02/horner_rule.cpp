#include <iostream>

// a0 + a1 * x + a2 * x ^ 2 + a3 * x ^ 3
// a0 + x(a1 + x(a2 + x(a3)))

int horner(int a[], int n, int x) {
    int y = 0;
    for (int i = n - 1; i >= 0; i--) {
        y = a[i] + y * x;
    }
    return y;
}

int main(int argc, char* argv[]) {
    int a[] = { 1, 2, 3 };
    int n = 3;
    std::cout << horner(a, n, 2);
    std::cout << "\n";
    return 0;
}