// http://info.mcip.ro/?cap=Programare%20dinamica ; ex #821

#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
    int n, m, a[100][100], dp[100][100], rez[100];
    cout << "n = "; cin >> n;
    cout << "m = "; cin >> m;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << "a[" << i << "]["  << j << "] = "; cin >> a[i][j];
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j ++) {
            if (i == 0) {
                dp[i][j] = 1;
                rez[j] = 1;
            } else if (a[i][j] > a[i - 1][j]) {
                dp[i][j] = dp[i - 1][j] + 1;
                if (dp[i][j] > rez[j]) rez[j] = dp[i][j];
            } else {
                dp[i][j] = 1;
            }
        }
    }

    for (int i = 0 ; i < n; i++) {
        for (int j = 0; j < m; j++) cout << dp[i][j] << " ";
        cout << endl;
    }

    for (int j = 0; j < m; j++) cout << rez[j] << " "; cout << endl;
    return 0;
}