/*
   exercise: 116
   page: 245
   description: sort matrix line
   command: echo 4 5 1 2 3 4 5 2 3 4 5 6 8 3 7 4 5 4 5 6 7 8 | ./program116
*/

#include <iostream>
#include <chrono>

#define PRINT_EXECUTION_DURATION 0

void read_matrix(int a[50][50], int &n, int &m) {
    std::cin >> n;
    std::cin >> m;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            std::cin >> a[i][j];
        }
    }
}

void print_matrix(int a[50][50], int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            std::cout << a[i][j] << " ";
        }
        std::cout << "\n";
    }
}

void swap_columns(int a[50][50], int n, int m, int i, int j) {
    for (int k = 0; k < n; k++) {
        int tmp = a[k][i];
        a[k][i] = a[k][j];
        a[k][j] = tmp;
    }
}

void sort_matrix_line(int a[50][50], int n, int m, int k) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m - 1; j++) {
            //std::cout << "pair{" << a[k][j] << " : " << a[k][j + 1] << "}\n";
            if (a[k][j] > a[k][j + 1]) {
                swap_columns(a, n, m, j, j + 1);
            }
        }
    }
}

int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();

    //... start code here

    int a[50][50], n, m;
    read_matrix(a, n, m);
    print_matrix(a, n, m);
    std::cout << "============\n";
    sort_matrix_line(a, n, m, 2);
    print_matrix(a, n, m);

    //... end code here

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    if (PRINT_EXECUTION_DURATION) {
        std::cout << "Execution time: " << duration.count() << " ms\n";
    }
    return 0;
}

