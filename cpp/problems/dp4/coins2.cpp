// cate monezi se folosesc in plata optima

#include <iostream>

int main(int argc, char *argv[]) {
    int n = 3, m = 13;
    int c[100] = {1, 4, 5};

    int dp[m + 1];
    for (int i = 0; i < m + 1; i++) dp[i] = INT_MAX;

    dp[0] = 0;
    for (int i = 0; i < n; i++) {
        dp[c[i]] = 1;
    }

    for (int j = 1; j <= m; j++) {
        int val = dp[j];
        for (int i = 0; i < n; i++) {
            if (j - c[i] > 0 && dp[j - c[i]] < INT_MAX) {
                if (val > dp[j - c[i]] + 1) { 
                    val = dp[j - c[i]] + 1;
                }
            }
        }
        dp[j] = val;
    }

    std::cout << dp[m] << "\n";
    return 0;
}
