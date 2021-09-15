#include <iostream>

void print(int *a, int n, int m) {
    int k = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) std::cout << a[k++] << " ";
        std::cout << "\n";
    }
}

int main(int argc, char *argv[]) {
    int n = 2, m = 5;
    int a[n][m];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) a[i][j] = i * m + j;
    }

    print(*a, n, m);

    return 0;
}
