/*
   exercise: 115
   page: 245
   description: matrix main diagonal
   command: echo 4 1 2 3 4 5 6 7 8 9 5 2 3 4 5 6 7 | ./program115
   command: echo 5 1 1 1 1 1 2 2 2 2 2 3 3 3 3 3 4 4 4 4 4 5 5 5 5 5 | ./program115
*/

#include <iostream>
#include <chrono>

#define PRINT_EXECUTION_DURATION 0

void read_matrix(int a[50][50], int &n) {
    std::cin >> n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            std::cin >> a[i][j];
        }
    }
}

void print_matrix(int a[50][50], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            std::cout << a[i][j] << " ";
        }
        std::cout << "\n";
    }
}

void main_diagonal_sum(int a[50][50], int n) {
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += a[i][i];
    }
    std::cout << sum << "\n";
}

void above_main_diagonal_sum(int a[50][50], int n) {
    int sum = 0;
    for (int i = 1; i < n; i++) {
        sum += a[i - 1][i];
    }
    std::cout << sum << "\n";
}

void below_main_diagonal_sum(int a[50][50], int n) {
    int sum = 0;
    for (int i = 1; i < n; i++) {
        sum += a[i][i - 1];
    }
    std::cout << sum << "\n";
}

void secondary_diagonal_sum(int a[50][50], int n) {
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += a[i][n - 1 - i];
    }
    std::cout << sum << "\n";
}

void above_secondary_diagonal_sum(int a[50][50], int n) {
    int sum = 0;
    for (int i = 1; i < n; i++) {
        sum += a[i - 1][n - 1 - i];
    }
    std::cout << sum << "\n";
}

void below_secondary_diagonal_sum(int a[50][50], int n) {
    int sum = 0;
    for (int i = 1; i < n; i++) {
        sum += a[i][n - i];
    }
    std::cout << sum << "\n";
}

int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();

    //... start code here

    int a[50][50], n;
    read_matrix(a, n);
    print_matrix(a, n);

    main_diagonal_sum(a, n);
    above_main_diagonal_sum(a, n);
    below_main_diagonal_sum(a, n);

    std::cout << "========\n";

    secondary_diagonal_sum(a, n);
    above_secondary_diagonal_sum(a, n);
    below_secondary_diagonal_sum(a, n);

    //... end code here

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    if (PRINT_EXECUTION_DURATION) {
        std::cout << "Execution time: " << duration.count() << " ms\n";
    }
    return 0;
}

