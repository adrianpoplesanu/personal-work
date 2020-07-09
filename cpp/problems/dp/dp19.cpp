// http://info.mcip.ro/?cap=Programare%20dinamica ; ex #398
#include <iostream>
#include <fstream>
#include <ctime>
using namespace std;

void afisare(int a[100][100], int drum[100][100], int i, int j) {
    if (drum[i][j] != -1) {
        afisare(a, drum, i - 1, drum[i][j]);
    }
    cout << a[i][j] << " ";
}

int main(int argc, char *argv[]) {
    clock_t start = clock();
    ifstream in("dp19.in");
    ofstream out("dp19.out");

    int n, a[100][100], dp[100][100], drum[100][100];
    in >> n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= i; j++)
            in >> a[i][j];
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= i; j++) {
            if (i == 0) {
                dp[i][j] = a[i][j];
                drum[i][j] = -1;
            } else if (j == 0) {
                dp[i][j] = a[i][j] + dp[i - 1][j];
                drum[i][j] = j;
            } else {
                if (dp[i - 1][j - 1] > dp[i - 1][j]) {
                    dp[i][j] = a[i][j] + dp[i - 1][j - 1];
                    drum[i][j] = j - 1;
                } else {
                    dp[i][j] = a[i][j] + dp[i - 1][j];
                    drum[i][j] = j;
                }
            }
        }
    }

    int max = dp[n - 1][0], maxj = 0;
    for (int i = 0; i < n; i++) {
        if (dp[n - 1][i] > dp[n - 1][maxj]) {
            maxj = i;
            max = dp[n - 1][i];
        }
    }

    cout << max << endl;
    afisare(a, drum, n - 1, maxj);
    cout << endl;

    in.close();
    out.close();
    clock_t end = clock();
    cout << "ran for " << (double)(end - start) / CLOCKS_PER_SEC << endl;
    return 0;
}