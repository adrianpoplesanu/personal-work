#include <iostream>

void print(int *a, int n, int m) {
    int k = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) std::cout << a[k++] << " ";
        std::cout << "\n";
    }
}

void print2(int *a, int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) std::cout << a[i * m + j] << " ";
        std::cout << "\n";
    }
}

int main(int argc, char *argv[]) {
    int n = 2, m = 5;
    int a[n][m];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) a[i][j] = i * m + j;
    }

    print2(*a, n, m);

    return 0;
}
