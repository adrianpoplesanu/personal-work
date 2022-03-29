#include <iostream>

void back(int a[], int k, int n, int m) {
    if (k == n) {
        for (int i = 0; i < n; i++) std::cout << a[i] << " ";
        std::cout << "\n";
    } else {
        a[k] = 1;
        while(a[k] < m) {
            back(a, k + 1, n, m);
            a[k]++;
        }
    }
}

int main(int argc, char *argv[]) {
    int a[] = {0, 0, 0};
    int n = 3;
    back(a, 0, n, 4);
    return 0;
}
