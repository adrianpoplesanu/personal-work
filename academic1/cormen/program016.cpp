/*
   exercise: 016
   page: 77
   description: square matrix multiply recursive
   command: echo 4 1 2 3 4 5 6 7 8 9 1 2 3 4 5 6 7 4 1 2 3 4 5 6 7 8 9 1 2 3 4 5 6 7 | ./program016
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

void square_matrix_multiply_recursive(int a[10][10], int b[10][10], int c[10][10], int aRow, int aCol, int bRow, int bCol, int cRow, int cCol, int n) {
    if (n == 1) {
        c[cRow][cCol] += a[aRow][aCol] * b[bRow][bCol];
        return;
    }

    int half = n / 2;

    // C11 += A11 * B11
    square_matrix_multiply_recursive(
            a, b, c,
            aRow, aCol,
            bRow, bCol,
            cRow, cCol,
            half);

    // C11 += A12 * B21
    square_matrix_multiply_recursive(
            a, b, c,
            aRow, aCol + half,
            bRow + half, bCol,
            cRow, cCol,
            half);

    // C12 += A11 * B12
    square_matrix_multiply_recursive(
            a, b, c,
            aRow, aCol,
            bRow, bCol + half,
            cRow, cCol + half,
            half);

    // C12 += A12 * B22
    square_matrix_multiply_recursive(
            a, b, c,
            aRow, aCol + half,
            bRow + half, bCol + half,
            cRow, cCol + half,
            half);

    // C21 += A21 * B11
    square_matrix_multiply_recursive(
            a, b, c,
            aRow + half, aCol,
            bRow, bCol,
            cRow + half, cCol,
            half);

    // C21 += A22 * B21
    square_matrix_multiply_recursive(
            a, b, c,
            aRow + half, aCol + half,
            bRow + half, bCol,
            cRow + half, cCol,
            half);

    // C22 += A21 * B12
    square_matrix_multiply_recursive(
            a, b, c,
            aRow + half, aCol,
            bRow, bCol + half,
            cRow + half, cCol + half,
            half);

    // C22 += A22 * B22
    square_matrix_multiply_recursive(
            a, b, c,
            aRow + half, aCol + half,
            bRow + half, bCol + half,
            cRow + half, cCol + half,
            half);
}

int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();

    //... start code here

    int a[10][10], b[10][10], c[10][10] = {0}, n;
    std::cin >> n;
    read_square_matrix(a, n);
    std::cin >> n;
    read_square_matrix(b, n);

    square_matrix_multiply_recursive(a, b, c, 0, 0, 0, 0, 0, 0, n);

    print_square_matrix(c, n);

    //... end code here

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    if (PRINT_EXECUTION_DURATION) {
        std::cout << "Execution time: " << duration.count() << " ms\n";
    }
    return 0;
}

