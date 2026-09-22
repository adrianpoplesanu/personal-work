/*
   exercise: 063
   page: 372
   description: matrix multiplication parenthesization
   command: echo 10 4 9 5 68 9 30 8 70 50 9 10 | ./program063
   command: echo 6 30 35 15 5 10 20 25 | ./program063
*/

#include <iostream>
#include <iomanip>
#include <chrono>

#define PRINT_EXECUTION_DURATION 0

void read_matrix_sizes(int p[50], int &n) {
    std::cin >> n;
    for (int i = 0; i <= n; i++) {
        std::cin >> p[i];
    }
}

void print_table(int a[50][50], int n, bool include_diagonal) {
    int width = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = include_diagonal ? i : i + 1; j <= n; j++) {
            int x = a[i][j];
            int w = (x <= 0);
            if (x < 0) {
                x = -x;
            }
            while (x > 0) {
                w++;
                x /= 10;
            }
            if (w > width) {
                width = w;
            }
        }
    }
    if (width < 2) {
        width = 2;
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (j < i || (!include_diagonal && j == i)) {
                std::cout << std::setw(width) << ".";
            } else {
                std::cout << std::setw(width) << a[i][j];
            }
            std::cout << " ";
        }
        std::cout << "\n";
    }
}

// algorithm 15.1 clrs
void matrix_chain_order(int p[50], int n, int m[50][50], int s[50][50]) {
    for (int i = 1; i <= n; i++) {
        m[i][i] = 0;
    }
    for (int l = 2; l <= n; l++) {
        for (int i = 1; i <= n - l + 1; i++) {
            int j = i + l - 1;
            m[i][j] = INT_MAX;
            for (int k = i; k <= j - 1; k++) {
                int q = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];
                if (q < m[i][j]) {
                    m[i][j] = q;
                    s[i][j] = k;
                }
            }
        }
    }
}

int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();

    //... start code here

    int p[50], n;
    read_matrix_sizes(p, n);

    int m[50][50], s[50][50];
    matrix_chain_order(p, n, m, s);

    print_table(m, n, true);
    std::cout << "\n";
    print_table(s, n, false);

    //... end code here

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    if (PRINT_EXECUTION_DURATION) {
        std::cout << "Execution time: " << duration.count() << " ms\n";
    }
    return 0;
}

