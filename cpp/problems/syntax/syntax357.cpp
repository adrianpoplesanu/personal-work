#include <iostream>

void init(int a[50][50], int &n) {
    n = 9;
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
    int a[50][50], n;

    init(a, n);    

    for (int l = 0; l < n; l++) {
        for (int i = 0; i < n - l; i++) {
            int j = i + l;
            a[i][j] = l + 1;
        }
    }

    print(a, n);

    return 0;
}
