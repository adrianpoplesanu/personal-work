// http://info.mcip.ro/?cap=Programare%20dinamica ; ex #202
#include <iostream>
#include <fstream>
#include <ctime>
using namespace std;

int main(int argc, char *argv[]) {
    int n;
    int a[100][100], dp[100][100];
    ifstream in("dp20.in");
    ofstream out("dp20.out");
    in >> n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            in >> a[i][j];
        }
    }

    int max = 0, pi = 0, pj = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i == 0) dp[i][j] = a[i][j];
            else if (j == 0) dp[i][j] = a[i][j];
            else {
                if (a[i][j] == 1) {
                    dp[i][j] = min(dp[i - 1][j], min(dp[i - 1][j - 1], dp[i][j - 1])) + 1;
                } else {
                    dp[i][j] = 0;
                }
            }
            if (max < dp[i][j]) {
                max = dp[i][j];
                pi = i + 1;
                pj = j + 1;
            }
        }
    }

    out << max << " " << pi - max + 1 << " " << pj - max + 1;
    in.close();
    out.close();
    return 0;
}
