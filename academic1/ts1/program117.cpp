/*
   exercise: 117
   page: 245
   description: sort principal diagonal
   command: echo 4 8 2 3 4 1 3 3 4 1 2 6 4 1 2 3 2 | ./program117
   command: echo 4 9 1 1 1 2 7 2 2 3 3 6 3 4 4 4 8 | ./program117
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

void swap_column(int a[50][50], int n, int k, int l) {
    for (int i = 0; i < n; i++) {
        int tmp = a[i][k];
        a[i][k] = a[i][l];
        a[i][l] = tmp;
    }
}

void swap_line(int a[50][50], int n, int k, int l) {
    for (int i = 0; i < n; i++) {
        int tmp = a[k][i];
        a[k][i] = a[l][i];
        a[l][i] = tmp;
    }
}

void swap(int a[50][50], int n, int k, int l) {
    swap_column(a, n, k, l);
    swap_line(a, n, k, l);
}

void sort_diagonal(int a[50][50], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n - 1; j++) {
            if (a[j][j] > a[j + 1][j + 1]) {
                swap(a, n, j, j + 1);
            }
        }
    }
}

int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();

    //... start code here

    int a[50][50], n;
    read_matrix(a, n);
    print_matrix(a, n);

    sort_diagonal(a, n);
    print_matrix(a, n);

    //... end code here

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    if (PRINT_EXECUTION_DURATION) {
        std::cout << "Execution time: " << duration.count() << " ms\n";
    }
    return 0;
}

