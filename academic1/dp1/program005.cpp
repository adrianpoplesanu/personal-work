/*
   exercise: 005
   page: https://info.mcip.ro/?cap=Programare%20dinamica
   description: #821
   command: echo 4 4 1 4 2 3 2 9 8 7 3 6 3 8 1 2 3 3 | ./program005
*/

#include <iostream>
#include <chrono>

#define PRINT_EXECUTION_DURATION 0

void read_matrix(int a[10][10], int &n, int &m) {
    std::cin >> n >> m;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            std::cin >> a[i][j];
        }
    }
}

void solve(int a[10][10], int n, int m) {
    int dp[10][10], i, j, max;
    for (i = 0; i < m; i++) {
        max = 1;
        for (j = 0; j < n; j++) {
            if (j == 0) dp[j][i] = 1;
            else if (a[j][i] > a[j - 1][i]) dp[j][i] = dp[j - 1][i] + 1;
            else dp[j][i] = 1;

            if (max < dp[j][i]) max = dp[j][i];
        }
        std::cout << max << " ";
    }
    std::cout << "\n---\n";

    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            std::cout << dp[i][j] << " ";
        }
        std::cout << "\n";
    }
}

int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();

    //... start code here

    int a[10][10], n, m;
    read_matrix(a, n, m);

    solve(a, n, m);

    //... end code here

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    if (PRINT_EXECUTION_DURATION) {
        std::cout << "Execution time: " << duration.count() << " ms\n";
    }
    return 0;
}

