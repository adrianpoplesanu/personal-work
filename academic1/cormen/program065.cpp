/*
   exercise: 065
   page: 385
   description: recursive matrix-chain multiplication
   command: echo 6 30 35 15 5 10 20 25 | ./program065
*/

#include <iostream>
#include <chrono>

#define PRINT_EXECUTION_DURATION 0

void read_matrix_sizes(int p[50], int &n) {
    std::cin >> n;
    for (int i = 0; i <= n; i++) {
        std::cin >> p[i];
    }
}

int recursive_matrix_chain(int p[50], int i, int j, int m[50][50]) {
    if (i == j) {
        return 0;
    }
    m[i][j] = INT_MAX;
    for (int k = i; k < j; k++) {
        int q = recursive_matrix_chain(p, i, k, m) + recursive_matrix_chain(p, k + 1, j, m) + p[i - 1] * p[k] * p[j];
        if (q < m[i][j]) {
            m[i][j] = q;
        }
    }
    return m[i][j];
}

int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();

    //... start code here

    int p[50], n;
    read_matrix_sizes(p, n);

    int m[50][50];
    recursive_matrix_chain(p, 1, n, m);

    std::cout << "Minimum number of multiplications is: " << m[1][n] << std::endl;

    //... end code here

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    if (PRINT_EXECUTION_DURATION) {
        std::cout << "Execution time: " << duration.count() << " ms\n";
    }
    return 0;
}

