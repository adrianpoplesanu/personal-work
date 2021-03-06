#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
    int n = 5;
    int a[10][10] = {
        {0, 0, 0, 0, 0},
        {0, 1, 0, 1, 0},
        {0, 1, 1, 1, 1},
        {0, 0, 0, 1, 1},
        {0, 1, 0, 1, 1}
    };

    int dp[10][10];
    int prev[10];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == 0) {
                dp[i][j] = a[i][j];
            } else {
                if (j == 0) {
                    dp[i][j] = a[i][j];
                } else {
                    if (a[i][j] == 1) {
                        dp[i][j] = max(dp[i - 1][j - 1], dp[i - 1][j + 1]) + 1;
                    } else {
                        dp[i][j] = dp[i - 1][j];
                    }
                }
            }
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << dp[i][j] << " ";
        }
        cout << "\n";
    }
    return 0;
}
