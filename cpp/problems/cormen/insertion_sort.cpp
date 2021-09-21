#include <iostream>

int main(int argc, char *argv[]) {
    int a[] = {6, 2, 9, 3, 7, 4, 1, 5};
    int n = 8;

    for (int i = 1; i < n; i++) {
        int current = a[i], j = i - 1;
        while(j >= 0 && a[j] > current) {
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = current;
    }

    for (int i = 0; i < n; i++) std::cout << a[i] << " ";
    std::cout << "\n";

    return 0;
}
