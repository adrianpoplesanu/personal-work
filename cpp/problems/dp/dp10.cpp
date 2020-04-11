// http://info.mcip.ro/?cap=Programare%20dinamica ; ex #408
// cerinta e gresita - te poti deplasa la birouri adiacente pe rand sau coloana doar spre stanga sau in jos

#include <fstream>
#include <iostream>
#include <ctime>
using namespace std;

int min(int a, int b) {
    if (a < b) return a;
    return b;
}

int main(int argc, char *argv[]) {
    clock_t start = clock();
    int n, m, a[100][100];
    int dp[100][100];
    ifstream in("dp10.in");
    ofstream out("dp10.out");
    in >> n >> m;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) in >> a[i][j];
    }
    in >> m;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (i == 0 && j == 0)
                dp[i][j] = a[i][j];
            else if (i == 0)
                dp[i][j] += a[i][j] + dp[i][j - 1];
            else if (j == 0)
                dp[i][j] += a[i][j] + dp[i - 1][j];
            else
                dp[i][j] += a[i][j] + min(dp[i - 1][j], dp[i][j - 1]);
        }
    }

    /*for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << dp[i][j] << " ";
        }
        cout << endl;
    }*/
    //cout << dp[n - 1][m - 1] << endl;
    out << dp[n - 1][m - 1];

    in.close();
    out.close();
    clock_t end = clock();
    cout << "ran for " << double(end - start) / CLOCKS_PER_SEC << "secs" << endl;
    return 0;
}