// http://info.mcip.ro/?cap=Programare%20dinamica ; ex #750

#include <iostream>
using namespace std;

int max(int a, int b) {
    if (a > b) return a;
    return b;
}

int main(int argc, char *argv[]) {
    int n, m, dp[100][100];
    cout << "n = "; cin >> n;
    cout << "m = "; cin >> m;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << "a[" << i << "]["  << j << "] = "; cin >> dp[i][j];
        }
    }
    for (int i = 0; i < n; i ++) {
        for (int j = 0; j < m; j++) {
            if (i == 0 && j == 0) continue;
            if (j == 0) {
                dp[i][j] += dp[i - 1][j];
                continue;
            }
            if (i == 0) {
                dp[i][j] += dp[i][j - 1];
                continue;
            }
            dp[i][j] += max(dp[i - 1][j], dp[i][j - 1]);
        }
    }
    cout << dp[n -1][m - 1] << endl;
    return 0;
}