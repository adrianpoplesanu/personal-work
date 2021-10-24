// longest palindrome subsequence
#include <iostream>

int max(int a, int b) {
    return a > b ? a : b;
}

void lcs(std::string str1, std::string str2) {
    int n = str1.length();
    int m = str2.length();

    int dp[n + 1][m + 1];

    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            if (i == 0 || j == 0) {
                dp[i][j] = 0;
            } else if (str1[i - 1] == str2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } else {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }

    /*for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            std::cout << dp[i][j] << " ";
        }
        std::cout << "\n";
    }*/

    int index = dp[n][m], max = index;
    char ans[index];

    int i = n, j = m;
    while (i > 0 && j > 0) {
        if (str1[i - 1] == str2[j - 1]) {
            ans[index - 1] = str1[i - 1];
            i--;
            j--;
            index--;
        } else if (dp[i - 1][j] > dp[i][j - 1]) {
            i--;
        } else {
            j--;
        }
    }

    for (int k = 0; k < max; k++) std::cout << ans[k];
    std::cout << "\n";
}

int main(int argc, char *argv[]) {
    std::string word = "qawbecrbtay";
    std::string rev = word;
    std::reverse(rev.begin(), rev.end());

    lcs(word, rev);
    return 0;
}
