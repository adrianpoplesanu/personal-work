#include <iostream>

#define STANGA_SUS 1
#define SUS 2
#define STANGA 3

void print_substring(std::string text, int *drum, int m) {
    if (m < 1 || drum[m] == 0) return;
    while (drum[m] == drum[m - 1]) m--;
    print_substring(text, drum, m - 1);
    std::cout << text[m - 1];
}

void walk_drum(int drum[100][100], std::string text, int i, int j) {
    if (i == 0 || j == 0) return;
    if (drum[i][j] == STANGA_SUS) {
        //std::cout << "aaa!";
        walk_drum(drum, text, i - 1, j - 1);
        std::cout << text[i]; 
    } else if (drum[i][j] == SUS) {
        //std::cout << "bbb=";
        walk_drum(drum, text, i, j - 1);
    } else if (drum[i][j] == STANGA) {
        //std::cout << "ccc-";
        walk_drum(drum, text, i - 1, j);
    }
}

int main(int argc, char* argv[]) {
    //std::string text1 = "abcdaaaefghijklmn";
    //std::string text2 = "tttbtethtjtktntttabcdaaaefghi";
    // abcdaaaefghi
    std::string text1 = "tttatbtctatttdttt";
    std::string text2 = "yyyyyayyyyyyyyybyyyayyyyyycyyyyydyyyy";
    // abcd
    int n = text1.size();
    int m = text2.size();
    int dp[n + 1][m + 1];
    int drum[100][100];

    for(int i = 0; i <= n; i++) {
        for(int j = 0; j <= m; j++) {
            dp[i][j] = 0;
            drum[i][j] = 0;
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (text1[i] == text2[j]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
                drum[i][j] = STANGA_SUS;
            }
            else {
                if (dp[i][j - 1] > dp[i - 1][j]) {
                    dp[i][j] = dp[i][j - 1];
                    drum[i][j] = SUS;
                } else {
                    dp[i][j] = dp[i - 1][j];
                    drum[i][j] = STANGA;
                }
            }
        }
    }

    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            std::cout << dp[i][j] << " ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";

    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            std::cout << drum[i][j] << " ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";

    //print_substring(text2, dp[n], m);
    walk_drum(drum, text1, n, m);
    std::cout << "\n";

    return 0;
}

/*
  c a b a c
a 0 1 1 1 1
a 0 1 1 2 2
c 1 1 1 1 3

  c a b c b d
a 0 1 1 1 1 1
c 1 1 1 2 2 2
b 0 0 2 2 3 3

*/
