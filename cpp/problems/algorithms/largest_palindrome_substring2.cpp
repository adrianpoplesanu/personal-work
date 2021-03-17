// Given a string, find the largest substring that is a palindrome
// dynamic programming

#include <iostream>
#include <string>
using namespace std;

int main(int argc, char *argv[]) {
    string s = "aaaabbbaabbb";
    int n = s.size();
    int dp[n][n];
    memset(dp, 0, sizeof(dp));
    int max = 0, imax, jmax;
    //for (int i = 0; i < n; i++) {
    //    for (int j = 0; j < n; j++) dp[i][j] = 0;
    //}

    for (int i = 0; i < n; i++) dp[i][i] = 1;

    for (int i = 0; i < n - 1; i++) if (s[i] == s[i + 1]) dp[i][i + 1] = 1; 

    for (int i = n - 1; i >= 0; i--) {
        for (int j = i + 1; j < n; j++) {
            if (j == i + 1 && s[i] == s[j]) {
                //dp[i][j] = 1;
            }
            else {
                if (s[i] == s[j]) {
                    dp[i][j] = dp[i + 1][j - 1] + 1;
                    if (max < dp[i][j]) {
                        max = dp[i][j];
                        imax = i;
                        jmax = j;
                    }
                }
            }
        }
    }

    //for (int i = 0; i < n; i++) {
    //    for (int j = 0; j < n; j++) cout << dp[i][j] << ' ';
    //    cout << '\n';
    //}
    //cout << imax << " " << jmax << " " << max << "\n";
    cout << s.substr (imax, jmax - 1) << "\n"; 

    return 0;
}
