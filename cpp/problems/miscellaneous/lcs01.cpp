#include <iostream>

int main(int argc, char *argv[]) {
    std::string text1 = "aaaaaaabaaaaaca";
    std::string text2 = "cbca";
    int n = text1.size(), m = text2.size();
    int dp[n + 1][m + 1];

    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            if (i == 0 || j == 0) {
                dp[i][j] = 0;
            } else if (text1[i - 1] == text2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } else {
                if (dp[i - 1][j] > dp[i][j - 1]) dp[i][j] = dp[i -1][j];
                else dp[i][j] = dp[i][j - 1];
            }
        }
    }

    for (int i = 1; i <=n; i++) {
        for (int j = 1; j <= m; j++) {
            std::cout << dp[i][j] << " ";
        }
        std::cout << "\n";
    }

    return 0;
}