#include <iostream>

int main(int argc, char* argv[]) {
    int a[] = {6, 3, 8, 4, 9, 2, 5, 1, 7};
    int n = 9;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (a[i] > a[j]) {
                int aux = a[i];
                a[i] = a[j];
                a[j] = aux;
            }
        }
    }
    for (int i = 0; i < n; i++) std::cout << a[i] << " ";
    std::cout << "\n";
    return 0;
}