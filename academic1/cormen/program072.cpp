/*
   exercise: 072
   page: 427
   description: 0-1 knapsack problem
   command: echo 3 10 60 20 100 30 120 50 | ./program072
*/

#include <iostream>
#include <chrono>

#define PRINT_EXECUTION_DURATION 0

void read(int v[50], int w[50],int &n, int &W) {
    std::cin >> n;
    for (int i = 1; i <= n; i++) {
        std::cin >> w[i] >> v[i];
    }
    std::cin >> W;
}

int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();

    //... start code here

    int v[50], w[50], n, W;
    read(v, w, n, W);

    int dp[50][W + 1];
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= W; j++) {
            dp[i][j] = 0;
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= W; j++) {
            if (j < w[i]) {
                dp[i][j] = dp[i - 1][j];
            } else {
                dp[i][j] = std::max(dp[i - 1][j], dp[i - 1][j - w[i]] + v[i]);
            }
        }
    }   

    std::cout << dp[n][W] << std::endl;

    //... end code here

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    if (PRINT_EXECUTION_DURATION) {
        std::cout << "Execution time: " << duration.count() << " ms\n";
    }
    return 0;
}

