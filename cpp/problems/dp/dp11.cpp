// http://info.mcip.ro/?cap=Programare%20dinamica ; ex #407

#include <fstream>
#include <iostream>
#include <ctime>
using namespace std;

void afisare_drum(int drum[100][100], int i, int j) {
    if (i > -1) {
        afisare_drum(drum, i - 1, drum[i][j]);
        cout << i + 1 << " " << j + 1 << endl;
    }
}

int main(int argc, char *argv[]) {
    clock_t start = clock();
    int n, a[100][100];
    int dp[100][100], drum[100][100];
    ifstream in("dp11.in");
    ofstream out("dp11.out");

    in >> n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) in >> a[i][j];
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == 0) {
                dp[i][j] = 0;
                drum[i][j] = 0;
            } else {
                if (a[i][j] == 0) {
                    drum[i][j] = j;
                    dp[i][j] = dp[i - 1][j];
                } else if (a[i][j] == 1) {
                    if (dp[i - 1][j - 1] >= dp[i - 1][j + 1]) {
                        dp[i][j] = 1 + dp[i - 1][j - 1];
                        drum[i][j] = j - 1;
                    } else {
                        dp[i][j] = 1 + dp[i - 1][j + 1];
                        drum[i][j] = j + 1;
                    }
                }
            }
        }
    }

    int max = dp[n - 1][0], pos = 0;
    for (int i = 1; i < n; i++) {
        if (dp[n - 1][i] > max) {
            max = dp[n - 1][i];
            pos = i;
        }
    }

    cout << max << endl;
    afisare_drum(drum, n - 1, pos);

    in.close();
    out.close();
    clock_t end = clock();
    cout << "ran for " << double(end - start) / CLOCKS_PER_SEC << "secs" << endl;
    return 0;
}