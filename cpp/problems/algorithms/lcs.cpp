#include <iostream>

int main(int argc, char *argv[]) {
    std::string text1 = "aaabbbccc";
    std::string text2 = "cabbca";
    int n = 9, m = 6;
    int dp[n][m];

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (i == 0 || j == 0) {
                dp[i][j] = 0;
            } else if (text1[i] == text2[j]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } else {
                if (dp[i - 1][j] > dp[i][j - 1]) dp[i][j] = dp[i - 1][j];
                else dp[i][j] = dp[i][j - 1];
            }
        }
    }

    int max = dp[n - 1][m - 1];
    char res[max + 1];
    res[max] = '\0';

    int i = n, j = m;
    while ( i > 0 && j > 0 ) {
        if (text1[i - 1] == text2[j - 1]) {
            res[max - 1] = text1[i - 1];
            i--;
            j--;
            max--;
        } else if (dp[i - 1][j] > dp[i][j - 1]) {
            i--;
        } else {
            j--;
        }
    }

    std::cout << res << "\n";
    return 0;
}
