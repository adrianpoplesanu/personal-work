// http://info.mcip.ro/?cap=Programare%20dinamica #750
#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
    int n = 3, m = 3;
    int a[10][10] = {
        {0, 4, 1},
        {0, 1, 1},
        {1, 0, 1}
    };
    int dp[n][m];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == 0 && j == 0) dp[i][j] = a[i][j];
            else if (i == 0) {
                dp[i][j] = dp[i][j - 1] + a[i][j];
            } else if (j == 0) {
                dp[i][j] = dp[i - 1][j] + a[i][j];
            }
            else {
                if (dp[i - 1][j] + a[i][j] > dp[i][j - 1] + a[i][j]) {
                    dp[i][j] = dp[i - 1][j] + a[i][j];
                } else {
                    dp[i][j] = dp[i][j - 1] + a[i][j];
                }
            }
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <  m; j++) cout << dp[i][j] << " ";
        cout << "\n";
    }
    return 0;
}
