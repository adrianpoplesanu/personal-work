// Given two strings, find the largest common substring
// dynamic programming
#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
    string s1 = "asdsaasdfdsssaaffaaaaaajta";
    string s2 = "afsaadsssadssfaaaaaajts";
    int n = 26, m = 22, size = 0, end = 0;
    int dp[n + 1][m + 1];
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            if (i == 0 || j == 0) {
                dp[i][j] = 0;
            } else if (s1[i - 1] == s2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
                //cout << dp[i][j];
                if (size < dp[i][j]) { end = i; size = dp[i][j]; }
            } else dp[i][j] = 0;
        }
    }
    //for(int i = 0; i < n + 1; i++) {
    //    for (int j = 0; j < m + 1; j++) cout << dp[i][j] << " ";
    //    cout << "\n";
    //}
    cout << end << " " << size << "\n";
    for (int i = end - size; i < end; i++) cout << s1[i];
    cout << "\n";
    return 0;
}
