/*
   exercise: 002
   page: https://info.mcip.ro/?cap=Programare%20dinamica
   description: #822
   command: ./program004
*/

#include <iostream>
#include <chrono>

#define PRINT_EXECUTION_DURATION 0

int max(int a, int b) {
    if (a > b) return a;
    return b;
}

int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();

    //... start code here

    int a[10][10] = {{1, 2, 3}, {-1, 3, 4}, {2, -1, 1}};
    int n = 3, i, j;
    int dp[10][10];

    for (i = n - 1; i >= 0; i--) {
        for (j = 0; j < n; j++) {
            if (i == n - 1 && j ==0) {
                dp[i][j] = a[i][j];
            } else if (i == n - 1) {
                dp[i][j] = a[i][j] + dp[i][j - 1];
            } else if (j == 0) {
                dp[i][j] = a[i][j] + dp[i + 1][j];
            } else {
                dp[i][j] = a[i][j] + max(max(dp[i + 1][j - 1], dp[i + 1][j]), dp[i][j - 1]);
            }
        }
    }

    for(i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            std::cout << dp[i][j] << " ";
        }
        std::cout << "\n";
    }

    //... end code here

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    if (PRINT_EXECUTION_DURATION) {
        std::cout << "Execution time: " << duration.count() << " ms\n";
    }
    return 0;
}

