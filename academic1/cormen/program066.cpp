/*
   exercise: 066
   page: 388
   description: matrix chain multiplication - memoization
   command: echo 6 30 35 15 5 10 20 25 | ./program066
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

int lookup_chain(int p[50], int i, int j, int m[50][50]) {
    if (m[i][j] < INT_MAX) {
        return m[i][j];
    }
    if (i == j) {
        m[i][j] = 0;
    } else {
        for (int k = i; k < j; k++) {
            int q = lookup_chain(p, i, k, m) + lookup_chain(p, k + 1, j, m) + p[i - 1] * p[k] * p[j];
            if (q < m[i][j]) {
                m[i][j] = q;
            }
        }
    }
    return m[i][j];
}

int memoized_matrix_chain(int p[50], int n, int m[50][50]) {
    for (int i = 1; i <= n; i++) {
        for (int j = i; j <= n; j++) {
            m[i][j] = INT_MAX;
        }
    }
    return lookup_chain(p, 1, n, m);
}

int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();

    //... start code here

    int p[50], n;
    read_matrix_sizes(p, n);

    int m[50][50];
    memoized_matrix_chain(p, n, m);

    std::cout << "[ RESULT ] " << m[1][n] << "\n";

    //... end code here

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    if (PRINT_EXECUTION_DURATION) {
        std::cout << "Execution time: " << duration.count() << " ms\n";
    }
    return 0;
}

