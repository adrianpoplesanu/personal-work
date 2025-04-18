#include <iostream>

/*

cel mai bun exemplu de memoizare pentru longest common substring

  t a t b t c t
z 0 0 0 0 0 0 0
a 0 1 1 1 1 1 1
z 0 1 1 1 1 1 1
b 0 1 1 2 2 2 2
z 0 1 1 2 2 2 2
c 0 1 1 2 2 3 3
z 0 1 1 2 2 3 3

*/

int main(int argc, char* argv[]) {
    std::string word1 = "tatbtct";
    std::string word2 = "zazbzcz";
    int n = word1.size();
    int m = word2.size();

    int dp[n + 1][m + 1];
    for (int i = 0; i <= n; i++) {
        dp[i][0] = 0;
    }
    for (int i = 0; i <= m; i++) {
        dp[0][i] = 0;
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (word1[i - 1] == word2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } else if (dp[i - 1][j] > dp[i][j - 1]) {
                dp[i][j] = dp[i - 1][j];
            } else {
                dp[i][j] = dp[i][j - 1];
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            std::cout << dp[i][j] << " ";
        }
        std::cout << "\n";
    }

    return 0;
}