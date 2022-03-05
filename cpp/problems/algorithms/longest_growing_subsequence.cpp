#include <iostream>

int main(int argc, char *argv[]) {
    int a[] = {1, 9, 2, 9, 3, 9, 4, 9, 2, 1, 0};
    int n = 11;
    int dp[n];

    for (int i = 0; i < n; i++) {
        dp[i] = 1;
        for (int j = 0; j < i; j++) {
            if (a[i] > a[j] && dp[j] + 1 > dp[i]) dp[i] = dp[j] + 1;
        }
    }

    for (int i = 0; i < n; i++) {
        std::cout << dp[i] << " ";
    }
    std::cout << "\n";
    return 0;
}
