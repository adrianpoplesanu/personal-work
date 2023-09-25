// toate modurile in care suma m poate fi platita folosind monezile {1, 4, 5}
#include <iostream>

int main(int argc, char *argv[]) {
    int n = 3, m = 150;
    int c[100] = {1, 4, 5};
    
    int dp[m + 1];
    memset(dp, 0, sizeof(dp));

    dp[0] = 1;
    for (int i = 0; i < n; i++) {
        for (int j = c[i]; j <= m; j++) {
            dp[j] += dp[j - c[i]];
        }
    }
    std::cout << dp[m] << "\n";

    return 0;
}
