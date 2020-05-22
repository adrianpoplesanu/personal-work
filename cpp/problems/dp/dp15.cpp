// http://info.mcip.ro/?cap=Programare%20dinamica ; ex #402

#include <iostream>
#include <fstream>
#include <ctime>
using namespace std;

int main(int argc, char *argv[]) {
    clock_t start = clock();
    ifstream in("dp15.in");
    ofstream out("dp15.out");

    int n, m, dp[100][100];
    in >> n >> m;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (i == 0) {
                dp[i][j] = 1;
            } else if (j == 0) {
                dp[i][j] = 1;
            } else {
                dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
            }
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << dp[i][j] << " ";
        }
        cout << endl;
    }
    cout << dp[n - 1][m - 1] << endl;

    in.close();
    out.close();
    clock_t end = clock();
    cout << "ran for " << (double)(end-start) / CLOCKS_PER_SEC << "secs" << endl;
    return 0;
}