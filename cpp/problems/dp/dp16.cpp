// http://info.mcip.ro/?cap=Programare%20dinamica ; ex #401

#include <iostream>
#include <fstream>
#include <ctime>
using namespace std;

int main(int argc, char *atgv[]) {
    ifstream in("dp16.in");
    ofstream out("dp16.out");

    int k, n, dp[100][100];
    in >> k >> n;

    dp[0][0] = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= i; j++)
            if (j == 0 || j == i) dp[i][j] = 1;
            else dp[i][j] = dp[i - 1][j] + dp[i - 1][j - 1];
    }
    cout << dp[n][k] << endl;

    in.close();
    out.close();
    return 0;
}