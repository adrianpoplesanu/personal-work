// http://info.mcip.ro/?cap=Programare%20dinamica #398
#include <iostream>
#include <fstream>
#include <ctime>
using namespace std;

int max(int a, int b) {
    if (a > b) return a;
    return b;
}

void afiseaza_drum(int a[100][100], int drum[100][100], int i, int j, ofstream &out) {
    if (i > 0) {
        afiseaza_drum(a, drum, i - 1, drum[i][j], out);
    }
    out << a[i][j] << " ";
}

int main(int argc, char *argv[]) {
    clock_t start = clock(), end;
    ifstream in("dp21.in");
    ofstream out("dp21.out");

    int n, a[100][100], dp[100][100], drum[100][100];
    in >> n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= i; j++) {
            in >> a[i][j];
        }
    }


    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= i; j++) {
            if (i == 0)  {
                dp[i][j] = a[i][j];
                drum[i][j] = i;
            }
            else {
                //dp[i][j] = a[i][j] + max(dp[i - 1][j - 1], dp[i - 1][j]);
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

    /*for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << dp[i][j] << " ";
        }
        cout << "\n";
    }*/

    int max = dp[n - 1][0], p = 0;
    for (int i = 0; i < n; i++) {
        if (dp[n - 1][i] > max) {
            max = dp[n - 1][i];
            p = i;
        }
    }

    afiseaza_drum(a, drum, n - 1, p, out);

    out << "\n";

    in.close();
    out.close();

    end = clock();
    cout << "ran for " << (double)(end - start) / CLOCKS_PER_SEC << "\n";
    return 0;
}
