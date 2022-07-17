#include <iostream>

int main(int argc, char* argv[]) {
    int a[] = { 2, 3, 8, 6, 1 };
    int n = 5;
    int inversions = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (a[i] > a[j]) {
                std::cout << a[i] << " " << a[j] << "\n";
                inversions++;
            }
        }
    }
    std::cout << inversions << "\n";
    return 0;
}