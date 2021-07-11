// http://info.mcip.ro/?cap=Programare%20dinamica #821
#include <iostream>

int max(int a, int b) {
    if (a > b) return a;
    return b;
}

int main(int argc, char *argv[]) {
    int n = 4, m = 4;
    int a[4][4] = {
        { 1, 4, 2, 3 },
        { 2, 9, 8, 7 },
        { 1, 6, 3, 8 },
        { 3, 2, 3, 3 }
    };
    for (int j = 0; j < m; j++) {
        int dp[n];
        memset(dp, 0, sizeof(dp));
        for (int i = 0; i < n; i++) {
            if (i == 0) dp[i] = 1;
            else {
                dp[i] = 1;
                for (int k = 0; k < i; k++) {
                    if (a[k][j] < a[i][j]) dp[i] = max(dp[i], dp[k] + 1);
                }
            }
        }
        int max = dp[0];
        for (int k = 1; k < n; k++) if (dp[k] > max) max = dp[k];
        std::cout << max << " ";
    }
    std::cout << "\n";
    return 0;
}
