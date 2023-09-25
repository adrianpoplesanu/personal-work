// minimum coins used to pay a sum, also show the coins used
#include <iostream>

int main(int argc, char *argv[]) {
    int n = 3, m = 13;
    int c[] = {1, 4, 5};

    int dp[m + 1];
    int d[m + 1];
    int uc[m + 1];
    for (int i = 0; i < m + 1; i++) {
        dp[i] = INT_MAX;
        d[i] = 0;
        uc[i] = 0;
    }

    dp[0] = 0;
    for (int i = 0; i < n; i++) {
        dp[c[i]] = 1;
        d[c[i]] = 0;
        uc[c[i]] = c[i];
    }

    for (int j = 1; j <= m; j++) {
        int val = dp[j];
        for (int i = 0; i < n; i++) {
            if (j - c[i] > 0 && dp[j - c[i]] < INT_MAX) {
                if (val > dp[j - c[i]] + 1) {
                    val = dp[j - c[i]] + 1;
                    d[j] = j - c[i];
                    uc[j] = c[i];
                }
            }
        }
        dp[j] = val;
    }

    std::cout << dp[m] << "\n";
    int pos = m;
    while(uc[pos]) {
        std::cout << uc[pos] << " ";
        pos = d[pos];
    }
    std::cout << "\n";

    return 0;
}
