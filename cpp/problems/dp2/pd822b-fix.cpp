// http://info.mcip.ro/?cap=Programare%20dinamica #822
#include <iostream>

int maximum(int a, int b, int c) {
    if (a >= b && a >= c) return a;
    if (b >= a && b >= c) return b;
    return c;
}

int main(int argc, char *argv[]) {
    int a[100][100] = {
        {1, 2, 3},
        {10, 3, 4},
        {2, -1, -1},
    }, n = 3;
    int dp[n][n];
    memset(dp, 0, sizeof(dp));

    for (int i = n - 1; i >= 0; i--) {
        for (int j = 0; j < n; j++) {
            if (i == n - 1 && j == 0) dp[i][j] = a[i][j];
            else if (i == n - 1) dp[i][j] = a[i][j] + dp[i][j - 1];
            else if (j == 0) dp[i][j] = a[i][j] + dp[i + 1][j];
            else dp[i][j] = a[i][j] + maximum(dp[i][j - 1], dp[i + 1][j - 1], dp[i + 1][j]);
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            std::cout << dp[i][j] << " ";
        }
        std::cout << "\n";
    }

    return 0;
}
