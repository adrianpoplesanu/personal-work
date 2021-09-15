#include <iostream>

#define STANGA_SUS 1
#define STANGA 2
#define SUS 4

void print(int drum[100][100], int dp[100][100], int n, int m, int i, int j, std::string word) {
    if (dp[i][j] == 0) return;
    if (drum[i][j] == STANGA_SUS) {
        print(drum, dp, n, m, i - 1, j - 1, word);
        std::cout << word[i - 1];
    } else if (drum[i][j] == STANGA) {
        print(drum, dp, n, m, i - 1, j, word);
    } else if (drum[i][j] == SUS) {
        print(drum, dp, n, m, i, j - 1, word);
    }
}

int main(int argc, char *argv[]) {
    std::string word1 = "tatttattttbttttctttctttdttt";
    //std::string word1 = "aabccdt";
    std::string word2 = "zazzzzabzzzcdczzzd";

    int n = word1.size();
    int m = word2.size();
    int dp[100][100];
    int drum[100][100];

    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            dp[i][j] = 0;
            drum[i][j] = 0;
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (word1[i - 1] == word2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
                drum[i][j] = STANGA_SUS;
            } else {
                if (dp[i - 1][j] > dp[i][j - 1]) {
                    dp[i][j] = dp[i - 1][j];
                    drum[i][j] = STANGA;
                }
                else {
                    dp[i][j] = dp[i][j - 1];
                    drum[i][j] = SUS;
                }
            }
        }
    }

    /*for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            std::cout << dp[i][j] << " ";
        }
        std::cout << "\n";
    }

    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            std::cout << drum[i][j] << " ";
        }
        std::cout << "\n";
    }

    int i = n, j = m;
    while (dp[i][j] != 0) {
        if (drum[i][j] == STANGA_SUS) {
            std::cout << word1[i - 1];
            i--; j--;
        } else if (drum[i][j] == STANGA) {
            i--;
        } else {
            j--;
        }
    }
    if (dp[i][j] == 0 && drum[i][j] == STANGA_SUS) std::cout << word1[i];
    std::cout << "\n";*/

    print(drum, dp, n, m, n, m, word1);
    std::cout << "\n";

    return 0;
}
