// http://info.mcip.ro/?cap=Programare%20dinamica ; ex #399

#include <iostream>
#include <fstream>
#include <ctime>
using namespace std;

void afisare_drum(int a[100][100], int drum[100][100], int i, int j, ofstream &out) {
    if (j != -1) {
        afisare_drum(a, drum, i - 1, drum[i][j], out);
        out << a[i][j] << " " << endl;
    }
}

int main(int argc, char *argv[]) {
    clock_t start = clock();
    ifstream in("dp18.in");
    ofstream out("dp18.out");

    int n, a[100][100], dp[100][100], max, jmax, drum[100][100];
    in >> n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) in >> a[i][j];
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == 0) {
                dp[i][j] = a[i][j];
                drum[i][j] = -1;
                continue;
            }
            if (j == 0) {
                dp[i][j] += dp[i - 1][j] + a[i][j];
                drum[i][j] = j;
                continue;
            }
            if (a[i - 1][j] > a[i - 1][j - 1]) {
                dp[i][j] = dp[i - 1][j] + a[i][j];
                drum[i][j] = j;
            } else {
                dp[i][j] = dp[i - 1][j - 1] + a[i][j];
                drum[i][j] = j - 1;
            }
        }
    }

    max = dp[n - 1][0];
    jmax = 0;
    for (int i = 1; i < n; i++) {
        if (dp[n - 1][i] > max) {
            jmax = i;
            max = dp[n - 1][i];
        }
    }

    out << max << endl;
    afisare_drum(a, drum, n - 1, jmax, out);

    in.close();
    out.close();
    clock_t end = clock();
    cout << "ran for: " << (double)(end - start) / CLOCKS_PER_SEC << "secs" << endl;
    return 0;
}