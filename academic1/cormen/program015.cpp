/*
   exercise: 015
   page: 75
   description: matrix multiplying
   command: echo 4 1 2 3 4 5 6 7 8 9 1 2 3 4 5 6 7 4 1 2 3 4 5 6 7 8 9 1 2 3 4 5 6 7 | ./program015
*/

#include <iostream>
#include <chrono>

#define PRINT_EXECUTION_DURATION 0

void read_matrix(int a[10][10], int &n) {
    int i, j;
    std::cin >> n;
    for(i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            std::cin >> a[i][j];
        }
    }
}

void print_matrix(int a[10][10], int n) {
    int i, j;
    for(i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            std::cout << a[i][j] << " ";
        }
        std::cout << "\n";
    }
}

void multiply(int a[10][10], int b[10][10], int c[10][10], int n) {
    int i, j, k;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            int sum = 0;
            for (k = 0; k < n; k++) {
                sum += a[i][k] * b[k][j];
            }
            c[i][j] = sum;
        }
    }
}

int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();

    //... start code here

    int a[10][10], b[10][10], c[10][10], n;
    read_matrix(a, n);
    read_matrix(b, n);

    multiply(a, b, c, n);
    print_matrix(c, n);

    //... end code here

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    if (PRINT_EXECUTION_DURATION) {
        std::cout << "Execution time: " << duration.count() << " ms\n";
    }
    return 0;
}

