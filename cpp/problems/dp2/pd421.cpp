#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
    int n = 3;
    int a[10][10] = {
        {1, 2, 1},
        {3, 6, 1},
        {1, 3, 6}
    };
    int dp[10][10];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == 0 && j== 0) dp[i][j] = a[i][j];
            else if (i == 0) {
                dp[i][j] = a[i][j] + dp[i][j - 1];
            } else if (j == 0) {
                dp[i][j] = a[i][j] + dp[i - 1][j];
            } else {
                dp[i][j] = a[i][j] + dp[i - 1][j] + dp[i][j - 1] - dp[i - 1][j - 1];
            }
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) cout << dp[i][j] << " ";
        cout << '\n';
    }
    cout << dp[2][2] - dp[0][2] - dp[2][0] + dp[0][0] << '\n';
    return 0;
}
