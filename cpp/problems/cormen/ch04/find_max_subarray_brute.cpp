#include <iostream>

int main(int argc, char* argv[]) {
    int a[] = {13, -3, -25, 20, -3, -16, -23, 18, 20, -7, 12, -5, -22, 15, -4, 7 };
    int n = 16;

    int max = -INT_MAX;
    int start, end;

    for (int i = 0; i < n; i++) {
        int suma = 0;
        for (int j = i; j < n; j++) {
            suma += a[j];
            if (max < suma) {
                max = suma;
                start = i;
                end = j;
            }
        }
    }

    std::cout << max << "\n" << start << "\n" << end << "\n";
    for (int i = start; i <= end; i++) std::cout << a[i] << " ";
    std::cout << "\n";
    return 0;
}
