// http://info.mcip.ro/?cap=Programare%20dinamica ; ex #400

#include <iostream>
#include <fstream>
#include <ctime>
using namespace std;

int max(int a, int b, int c) {
    if (a > b && a > c) return a;
    if (b > c && b > a) return b;
    return c;
}

int main(int argc, char *argv[]) {
    clock_t start = clock();

    ifstream in("dp17.in");
    ofstream out("dp17.out");

    int n, a[100][100], dp[100][100];
    in >> n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) in >> a[i][j];
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == 0) dp[i][j] = a[i][j];
            else {
                dp[i][j] = max(dp[i - 1][j - 1], dp[i - 1][j], dp[i - 1][j + 1]) + a[i][j];
            }
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) cout << dp[i][j] << " ";
        cout << endl;
    }

    in.close();
    out.close();
    clock_t end = clock();
    cout << "ran for " << (double)(end - start) / CLOCKS_PER_SEC << "secs" << endl;
    return 0;
}