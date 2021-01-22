// http://info.mcip.ro/?cap=Programare%20dinamica #822
// e o problema clasica de calcul al drumului intr-o matrice
#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
    int a[100][100] = {
        {1, 2, 3, 4},
        {-1, 3, 4, 2},
        {2, -1, -1, 2},
        {5, -2, -1, -2}
    }, n = 4;
    int dp[n][n];
    for (int i = n - 1; i >= 0; i--) {
        for (int j = 0; j < n; j++) {
            if (i == n - 1 || j == 0) dp[i][j] = 1;
            else {
                dp[i][j] = dp[i][j - 1] + dp[i + 1][j - 1] + dp[i + 1][j];
            }
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) cout << dp[i][j] << " ";
        cout << "\n";
    }
    return 0;
}
