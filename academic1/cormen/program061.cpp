/*
   exercise: 061
   page: 370
   description: matrix-chain multiplication
   command: echo 3 2 1 2 3 4 5 6 2 4 1 2 3 4 5 6 7 8 | ./program061
*/

#include <iostream>
#include <chrono>

#define PRINT_EXECUTION_DURATION 0

void read_matrix(int a[50][50], int &n, int &m) {
    std::cin >> n >> m;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            std::cin >> a[i][j];
        }
    }
}

void print_matrix(int a[50][50], int n, int m) {
    std::cout << "[ MATRIX ]\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            std::cout << a[i][j] << " ";
        }
        std::cout << "\n";
    }
}

void matrix_multiply(int a[50][50], int n1, int m1, int b[50][50], int n2, int m2, int c[50][50], int &n3, int &m3) {
    if (m1 != n2) {
        std::cout << "[ ERROR ] incompatible dimensions";
        return;
    }
    n3 = n1;
    m3 = m2;
    for (int i = 0; i < n3; i++) {
        for (int j = 0; j < m3; j++) {
            c[i][j] = 0;
            for (int k = 0; k < m1; k++) {
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }
}

int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();

    //... start code here

    int a[50][50], n1, m1;
    read_matrix(a, n1, m1);
    print_matrix(a, n1, m1);

    int b[50][50], n2, m2;
    read_matrix(b, n2, m2);
    print_matrix(b, n2, m2);

    int c[50][50], n3, m3;
    matrix_multiply(a, n1, m1, b, n2, m2, c, n3, m3);
    print_matrix(c, n3, m3);

    //... end code here

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    if (PRINT_EXECUTION_DURATION) {
        std::cout << "Execution time: " << duration.count() << " ms\n";
    }
    return 0;
}

