// cerinta e formulata gresit
#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
    int a[10][10] = {
        {3, 7, 2},
        {6, 4, 3},
        {6, 3, 1},
        {6, 2, 2}
    };
    int n = 4, m = 3, dp[10][10];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (i == 0 && j == 0) dp[i][j] = a[i][j];
            else if (i == 0) dp[i][j] = a[i][j] + dp[i][j - 1];
            else if (j == 0) dp[i][j] = a[i][j] + dp[i - 1][j];
            else {
                dp[i][j] = a[i][j] + min(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }
    cout << dp[n - 1][m - 1] << "\n";
    return 0;
}
