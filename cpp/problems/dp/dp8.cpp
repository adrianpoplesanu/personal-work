// http://info.mcip.ro/?cap=Programare%20dinamica ; ex #736

#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
    int n, k;
    int dp[100][100];
    cout << "n = "; cin >> n;
    cout << "k = "; cin >> k;

    dp[0][0] = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= i; j++) {
            if (j == 0) {
                dp[i][j] = 1;
            } else {
                dp[i][j] = dp[i - 1][j - 1] + dp[i - 1][j];
            }
        }
    }
    cout << dp[n][k] << endl;
    return 0;
}