// http://info.mcip.ro/?cap=Programare%20dinamica #402
#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
    int n = 3, m = 3;
    int dp[n][m];
    memset(dp, 0, sizeof(dp));
    for (int i = 0; i < n; i++) {
        dp[i][0] = 1;
    }
    for (int i = 0; i < m; i++) {
        dp[0][i] = 1;
    }
    for (int i = 1; i < n; i++) {
        for (int j = 1; j < m; j++) dp[i][j] = dp[i][j - 1] + dp[i - 1][j];
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) cout << dp[i][j] << " ";
        cout << "\n";
    }
    return 0;
}
