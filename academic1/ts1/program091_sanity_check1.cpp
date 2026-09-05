/*
   exercise: 091 dp sanity check 1
   page: 238
   description: subset sum problem
   command: echo 5 3 7 4 2 9 19 | ./program091_sanity_check1
*/

#include <iostream>
#include <chrono>

#define PRINT_EXECUTION_DURATION 0

void print_drum(int a[50], int dp[50][1001], int n, int s, int i, int j) {
    if (i <= 0) return;

    if (dp[i - 1][j] == 1) {
        print_drum(a, dp, n, s, i - 1, j);
    } else {
        std::cout << a[i] << "\n";
        print_drum(a, dp, n, s - a[i], i - 1, j - a[i]);
    }
}

int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();

    //... start code here

    int a[50], n, S;
    int dp[50][1001];

    std::cin >> n;
    for (int i = 1; i <= n; i++) {
        std::cin >> a[i];
    }
    std::cin >> S;

    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= S; j++) {
            dp[i][j] = 0;
        }
    }

    dp[0][0] = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= S; j++) {
            if (dp[i - 1][j] == 1) {
                dp[i][j] = 1;
                if (j + a[i] <= S) {
                    dp[i][j + a[i]] = 1;
                }
            }
        }
    }

    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= S; j++) {
            std::cout << dp[i][j] << " ";
        }
        std::cout << "\n";
    }

    print_drum(a, dp, n, S, 5, 19);

    //... end code here

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    if (PRINT_EXECUTION_DURATION) {
        std::cout << "Execution time: " << duration.count() << " ms\n";
    }
    return 0;
}

