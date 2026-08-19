/*
   exercise: 118
   page: 245
   description: determine peaks
   command: echo 4 4 5 1 2 3 4 5 2 3 4 5 6 8 3 7 4 5 4 5 6 7 8 | ./program118
*/

#include <iostream>
#include <chrono>

#define PRINT_EXECUTION_DURATION 0

void read_matrix(int a[50][50], int &n, int &m) {
    std::cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            std::cin >> a[i][j];
        }
    }
    for (int i = 0; i <= n + 1; i++) {
        a[0][i] = INT_MIN;
        a[i][0] = INT_MIN;
        a[n + 1][i] = INT_MIN;
        a[i][n + 1] = INT_MIN;
    }
}

void print_matrix(int a[50][50], int n, int m) {
    for (int i = 0; i <= n + 1; i++) {
        for (int j = 0; j <= m + 1; j++) {
            std::cout << a[i][j] << " ";
        }
        std::cout << "\n";
    }
}

bool is_peak(int a[50][50], int n, int m, int i, int j) {
    return a[i][j] > a[i - 1][j - 1] && a[i][j] > a[i - 1][j] && a[i][j] > a[i - 1][j + 1]
            && a[i][j] > a[i][j - 1] && a[i][j] > a[i][j + 1]
            && a[i][j] > a[i + 1][j - 1] && a[i][j] > a[i + 1][j] && a[i][j] > a[i + 1][j + 1];
}

void determine_peaks(int a[50][50], int n, int m) {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (is_peak(a, n, m, i, j)) {
                std::cout << "1 ";
            } else {
                std::cout << "0 ";
            }
        }
        std::cout << "\n";
    }
}

int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();

    //... start code here

    int a[50][50], n, m;
    read_matrix(a, n, m);
    print_matrix(a, n, m);
    determine_peaks(a, n, m);

    //... end code here

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    if (PRINT_EXECUTION_DURATION) {
        std::cout << "Execution time: " << duration.count() << " ms\n";
    }
    return 0;
}

