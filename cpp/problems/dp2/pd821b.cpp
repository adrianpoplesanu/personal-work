// #821 http://info.mcip.ro/?cap=Programare%20dinamica
// o matrice, pentru fiecare coloana sa se afiseze numarul de elemente din cel mai lung subsir crescator
// asta e fara secventa consecutiva
#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
    int a[10][10] = {
        {1, 4, 2, 3},
        {2, 9, 8, 7},
        {3, 6, 3, 8},
        {1, 2, 3, 3}
    }, n = 4;
    int dp[n];
    for (int k = 0; k < n; k++) {
        memset(dp, 0, n);
        for (int i = 0; i < n; i++) {
            if (i == 0) dp[0] = 1;
            else {
                dp[i] = 1;
                for (int j = 0; j < i; j++) {
                    if (a[j][k] < a[i][k] && dp[i] < dp[j] + 1) { dp[i] = dp[j] + 1; }
                }
            }
        }
        int max = dp[0];
        for (int i = 1; i < n; i++) if (max < dp[i]) max = dp[i];
        cout << max << " ";
    }
    cout << "\n";
    return 0;
}
