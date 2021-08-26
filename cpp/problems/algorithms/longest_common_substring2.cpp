#include <iostream>

#define STANGA_SUS 1
#define SUS 2
#define STANGA 3

void print(int drum[100][100], std::string text, int i, int j) {
    if (i == 0 || j == 0) {
        if (drum[i + 1][j + 1] == STANGA_SUS) std::cout << text[i]; // if-ul asta nu era in cormen, a trebuit sa-l adaug eu
        return;
    }
    if (drum[i][j] == STANGA_SUS) {
        print(drum, text, i - 1, j - 1);
        std::cout << text[i];
    } else if (drum[i][j] == SUS) {
        print(drum, text, i - 1, j);
    } else {
        print(drum, text, i, j - 1);
    }
}

int main(int argc, char* argv[]) {
    int dp[100][100], drum[100][100];
    std::string text1 = "abcdaaaefghijklmn";
    std::string text2 = "tttbtethtjtktntttabcdaaaefghi";
    // abcdaaaefghi
    //std::string text1 = "tttatbtctatttdttt";
    //std::string text2 = "yyyyyayyyyyyyyybyyyayyyyyycyyyyydyyyy";
    // abcd
    //std::string text1 = "abc";
    //std::string text2 = "abc";
    // abc
    int m = text1.size();
    int n = text2.size();
    for (int i = 0; i < m; i++) dp[i][0] = 0;
    for (int j = 0; j < n; j++) dp[0][j] = 0;
    for (int i = 1; i < m; i++) {
        for (int j = 1; j < n; j++) {
            if (text1[i] == text2[j]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
                drum[i][j] = STANGA_SUS;
            } else if (dp[i - 1][j] >= dp[i][j - 1]) {
                dp[i][j] = dp[i - 1][j];
                drum[i][j] = SUS;
            } else {
                dp[i][j] = dp[i][j - 1];
                drum[i][j] = STANGA;
            }
        }
    }

    /*for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) std::cout << dp[i][j] << " ";
        std::cout << "\n";
    }
    std::cout << "\n";

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) std::cout << drum[i][j] << " ";
        std::cout << "\n";
    }
    std::cout << "\n";*/

    print(drum, text1, m - 1, n - 1);
    std::cout << "\n";
    return 0;
}
