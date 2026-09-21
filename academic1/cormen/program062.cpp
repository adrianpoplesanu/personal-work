/*
   exercise: 062
   page: 371
   description: matrix multiplication with enclosing type
   command: echo 3 2 1 2 3 4 5 6 2 4 1 2 3 4 5 6 7 8 | ./program062
*/

#include <iostream>
#include <chrono>

#define PRINT_EXECUTION_DURATION 0

struct Matrix {
    int n, m;
    int a[50][50];
};

void read_matrix(Matrix &mat) {
    std::cin >> mat.n >> mat.m;
    for (int i = 0; i < mat.n; i++) {
        for (int j = 0; j < mat.m; j++) {
            std::cin >> mat.a[i][j];
        }
    }
}

void print_matrix(Matrix mat) {
    std::cout << "[ MATRIX ]\n";
    for (int i = 0; i < mat.n; i++) {
        for (int j = 0; j < mat.m; j++) {
            std::cout << mat.a[i][j] << " ";
        }
        std::cout << "\n";
    }
}

Matrix multiply_matrix(Matrix matA, Matrix matB) {
    Matrix res;
    if (matA.m != matB.n) {
        std::cout << "[ ERROR ] incompatible dimensions\n";
        return res;
    }
    res.n = matA.n;
    res.m = matB.m;
    for (int i = 0; i < res.n; i++) {
        for (int j = 0; j < res.m; j++) {
            res.a[i][j] = 0;
            for (int k = 0; k < matA.m; k++) {
                res.a[i][j] += matA.a[i][k] * matB.a[k][j];
            }
        }
    }
    return res;
}

int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();

    //... start code here

    Matrix A, B;
    read_matrix(A);
    print_matrix(A);
    read_matrix(B);
    print_matrix(B);
    Matrix C = multiply_matrix(A, B);
    print_matrix(C);

    //... end code here

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    if (PRINT_EXECUTION_DURATION) {
        std::cout << "Execution time: " << duration.count() << " ms\n";
    }
    return 0;
}

