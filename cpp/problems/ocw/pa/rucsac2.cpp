#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
    int n = 5, W = 3;
    int w[20] = {2, 3, 1, 1, 2};
    int p[20] = {6, 3, 2, 8, 5};
    int dp[n + 1][W + 1];

    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= W; j++) {
             if (i == 0) dp[i][j] = 0;
             else {
                 dp[i][j] = dp[i - 1][j];
                 if (j - w[i - 1] >= 0) {
                     dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - w[i - 1]] + p[i - 1]);
                 }
             }
        }
    }
    cout << dp[n][W] << "\n";
    return 0;
}
