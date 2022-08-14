// longest sequential substring
#include <iostream>

int main(int argc, char* argv[]) {
    std::string text1 = "bebe-ramunitz-dex";
    std::string text2 = "adish-ramunitz-bebe";

    int n = text1.length();
    int m = text2.length(); 

    int dp[n][m];

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (text1[i] == text2[j]) {
                if (i == 0 || j == 0) dp[i][j] = 1;
                else dp[i][j] = dp[i - 1][j - 1] + 1;
            } else {
                dp[i][j] = 0;
            }
        }
    }

    /*for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            std::cout << dp[i][j] << " ";
        }
        std::cout << "\n";
    }*/

    int max = dp[0][0];
    int di;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (max < dp[i][j]) {
                max = dp[i][j];
                di = i;
            }
        }
    }

    std::cout << text1.substr(di - max + 1, max) << "\n";

    return 0;
}
