/*
   exercise: 017
   page: 82
   description: strassen algorythm
   command: echo 4 1 2 3 4 5 6 7 8 9 1 2 3 4 5 6 7 4 1 2 3 4 5 6 7 8 9 1 2 3 4 5 6 7 | ./program017
*/

#include <iostream>
#include <chrono>

#define PRINT_EXECUTION_DURATION 0

void read_square_matrix(int a[10][10], int n) {
    int i, j;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            std::cin >> a[i][j];
        }
    }
}

void print_square_matrix(int a[10][10], int n) {
    int i, j;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            std::cout << a[i][j] << " ";
        }
        std::cout << "\n";
    }
}

void add(int a[10][10], int b[10][10], int c[10][10], int n) {
    int i, j;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            c[i][j] = a[i][j] + b[i][j];
        }
    }
}

void sub(int a[10][10], int b[10][10], int c[10][10], int n) {
    int i, j;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            c[i][j] = a[i][j] - b[i][j];
        }
    }
}

void strassen(int a[10][10], int b[10][10], int c[10][10], int n) {
    if (n == 1) {
        c[0][0] = a[0][0] * b[0][0];
        return;
    }

    int half = n / 2;

    int a11[10][10], a12[10][10], a21[10][10], a22[10][10];
    int b11[10][10], b12[10][10], b21[10][10], b22[10][10];

    int m1[10][10], m2[10][10];

    int p1[10][10] = {0};
    int p2[10][10] = {0};
    int p3[10][10] = {0};
    int p4[10][10] = {0};
    int p5[10][10] = {0};
    int p6[10][10] = {0};
    int p7[10][10] = {0};

    int i, j;

    for (i = 0; i < half; i++) {
        for (j = 0; j < half; j++) {
            a11[i][j] = a[i][j];
            a12[i][j] = a[i][j + half];
            a21[i][j] = a[i + half][j];
            a22[i][j] = a[i + half][j + half];

            b11[i][j] = b[i][j];
            b12[i][j] = b[i][j + half];
            b21[i][j] = b[i + half][j];
            b22[i][j] = b[i + half][j + half];
        }
    }

    sub(b12, b22, m1, half);
    strassen(a11, m1, p1, half);

    add(a11, a12, m1, half);
    strassen(m1, b22, p2, half);

    add(a21, a22, m1, half);
    strassen(m1, b11, p3, half);

    sub(b21, b11, m1, half);
    strassen(a22, m1, p4, half);

    add(a11, a22, m1, half);
    add(b11, b22, m2, half);
    strassen(m1, m2, p5, half);

    sub(a12, a22, m1, half);
    add(b21, b22, m2, half);
    strassen(m1, m2, p6, half);

    sub(a11, a21, m1, half);
    add(b11, b12, m2, half);
    strassen(m1, m2, p7, half);

    int c11[10][10];
    int c12[10][10];
    int c21[10][10];
    int c22[10][10];

    add(p5, p4, m1, half);
    sub(m1, p2, m2, half);
    add(m2, p6, c11, half);

    add(p1, p2, c12, half);

    add(p3, p4, c21, half);

    add(p5, p1, m1, half);
    sub(m1, p3, m2, half);
    sub(m2, p7, c22, half);

    for (i = 0; i < half; i++) {
        for (j = 0; j < half; j++) {
            c[i][j] = c11[i][j];
            c[i][j + half] = c12[i][j];
            c[i + half][j] = c21[i][j];
            c[i + half][j + half] = c22[i][j];
        }
    }
}

int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();

    //... start code here

    int a[10][10], b[10][10], c[10][10], n;
    std::cin >> n;
    read_square_matrix(a, n);
    std::cin >> n;
    read_square_matrix(b, n);

    strassen(a, b, c, n);

    print_square_matrix(c, n);


    //... end code here

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    if (PRINT_EXECUTION_DURATION) {
        std::cout << "Execution time: " << duration.count() << " ms\n";
    }
    return 0;
}

