// TS1 e2 p141 pdf
#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
    int a[10][10], n, nr = 1;
    cout << "n = "; cin >> n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            //cout << "a[" << i << "," << j << "] = "; cin >> a[i][j];
            a[i][j] = nr++;
        }
    }
    for (int i = 0; i < n / 2 + 1; i++) {
        for (int j = i; j < n - i; j++) cout << a[i][j] << " ";
        for (int j = i + 1; j < n - i; j++) cout << a[j][n - i - 1] << " ";
        for (int j = n - 1 - 1 - i; j >= i; j--) cout << a[n - i - 1][j] << " ";
        for (int j = n - 1 - 1 - i; j > i; j--) cout << a[j][i] << " ";
    }
    cout << endl;
    return 0;
}
