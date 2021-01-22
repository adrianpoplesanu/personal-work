// http://info.mcip.ro/?cap=Programare%20dinamica #822
// e o problema clasica de calcul al drumului intr-o matrice
#include <iostream>
using namespace std;

int maximum(int a, int b, int c) {
    if (a >= b && a >= c) return a;
    if (b >= a && b >= c) return b;
    if (c >= a && c >= b) return c;
    return a;
}

int main(int argc, char *argv[]) {
    int a[100][100] = {
        {1, 2, 3},
        {-1, 3, 4},
        {2, -1, -1},
    }, n = 3;
    int dp[n][n];
    for (int i = n - 1; i >= 0; i--) {
        for (int j = 0; j < n; j++) {
            if (i == n - 1 || j == 0) dp[i][j] = a[i][j];
            else {
                dp[i][j] = a[i][j] + maximum(dp[i][j - 1], dp[i + 1][j - 1], dp[i + 1][j]);
            }
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) cout << dp[i][j] << " ";
        cout << "\n";
    }
    return 0;
}
