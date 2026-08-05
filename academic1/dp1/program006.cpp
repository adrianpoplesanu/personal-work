/*
   exercise: 006
   page: https://info.mcip.ro/?cap=Programare%20dinamica
   description: #750
   command: echo 3 3 0 4 1 0 1 1 1 0 1 | ./program006
*/

#include <iostream>
#include <chrono>

#define PRINT_EXECUTION_DURATION 0

void read_matrix(int a[50][50], int &n, int &m) {
    int i, j;
    std::cin >> n >> m;
    for(i = 0; i < n; i++) {
        for(j = 0; j < m; j++) {
            std::cin >> a[i][j];
        }
    }
}

int max(int a, int b) {
    if (a > b) return a;
    return b;
}

void arici(int a[50][50], int n, int m) {
    int dp[50][50], i, j;
    for (i = 0; i < n; i++) {
        for(j = 0; j < m; j++) {
            if (i == 0 && j == 0) {
                dp[i][j] = a[i][j];
            } else if (i == 0) {
                dp[i][j] = a[i][j] + dp[i][j - 1];
            } else if (j == 0) {
                dp[i][j] = a[i][j] + dp[i - 1][j];
            } else {
                dp[i][j] = a[i][j] + max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }
    std::cout << "[ RESULT ] " << dp[n - 1][m - 1] << "\n";
}

int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();

    //... start code here

    int a[50][50], n, m;
    read_matrix(a, n, m);
    arici(a, n, m);

    //... end code here

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    if (PRINT_EXECUTION_DURATION) {
        std::cout << "Execution time: " << duration.count() << " ms\n";
    }
    return 0;
}

