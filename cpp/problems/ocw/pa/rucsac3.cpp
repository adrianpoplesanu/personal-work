// imi place mai mult varianta mea decat cea pe care o dau ei in cursul de pa
// in plus, varianta lor, nu merge daca elementul de la index-ul 0 e in lista de elemente alese
// aceesi problema pare sa fie si pe pagina de wikipedia, solutiile lor par gresite
#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
    int n = 5, W = 3;
    int w[20] = {1, 3, 1, 1, 2};
    int p[20] = {6, 3, 2, 8, 5};
    int dp[n + 1][W + 1];

    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= W; j++) {
             if (i == 0) {
                 dp[i][j] = 0;
                 if (j - w[i] >= 0) dp[i][j] = p[i];
             }
             else {
                 dp[i][j] = dp[i - 1][j];
                 if (j - w[i] >= 0) {
                     dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - w[i]] + p[i]);
                 }
             }
        }
    }
    cout << dp[n - 1][W] << "\n";
    return 0;
}
