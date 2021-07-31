// http://info.mcip.ro/?cap=Programare%20dinamica #822
#include <iostream>

int main(int argc, char *argv[]) {
    int n = 3;
    int a[3][3] = {
        {1, 2, 3},
        {-1, 3, 4},
        {2, -1, -1}
    };
    int dp[n][n];

    for (int i = n - 1; i >=0; i--) {
        for (int j = 0; j < n; j++) {
            if (i == n - 1 || j == 0) dp[i][j] = 1;
            else dp[i][j] = dp[i][j - 1] + dp[i + 1][j - 1] + dp[i + 1][j];
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
