/*
   exercise: 822
   page: https://info.mcip.ro/?cap=Programare%20dinamica
   description: simle parsing
   command: echo 3 1 2 3 -1 3 4 2 -1 -1 | ./dp01
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

int max(int a, int b, int c) {
    return std::max(a, std::max(b, c));
}

int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();

    //... start code here

    int a[50][50];
    int n;
    read_matrix(a, n);
    print_matrix(a, n);

    int dp[50][50];
    for (int i = n - 1; i >= 0; i--) {
        for (int j = 0; j < n; j++) {
            if (i == n - 1 && j == 0) {
                dp[i][j] = a[i][j];
            } else if (j == 0) {
                dp[i][j] = dp[i + 1][j] + a[i][j];
            } else if (i == n - 1) {
                dp[i][j] = dp[i][j - 1] + a[i][j];
            } else {
                dp[i][j] = a[i][j] + max(dp[i + 1][j], dp[i][j - 1], dp[i + 1][j - 1]);
            }
        }
    }

    print_matrix(dp, n);
    std::cout << dp[0][n - 1] << "\n";

    //... end code here

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    if (PRINT_EXECUTION_DURATION) {
        std::cout << "Execution time: " << duration.count() << " ms\n";
    }
    return 0;
}

