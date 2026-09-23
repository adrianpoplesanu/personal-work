#include <iostream>

void init(int a[50][50], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            a[i][j] = 0;
        }
    }
}

void print(int a[50][50], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            std::cout << a[i][j] << " ";
        }
        std::cout << "\n";
    }
}

int main(int argc, char *argv[]) {
    int a[50][50];
    int n = 10;
    int step = 1;

    init(a, 50);

    for (int i = 0; i < n; i++) {
        a[i][i] = step;
    }

    for (int l = 1; l < n; l++) {
        step++;
        for (int i = 0; i < n - l; i++) {
            int j = i + l;
            a[i][j] = step;
        }
    }

    print(a, 50);

    return 0;
}
