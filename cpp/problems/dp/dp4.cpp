// http://info.mcip.ro/?cap=Programare%20dinamica ; ex #822

#include <iostream>
using namespace std;

int max(int a, int b, int c) {
    if ((a >= b) && (a >= c)) return a;
    if ((b >= a) && (b >= c)) return b;
    if ((c >= a) && (c >= b)) return c;
    return -10000;
}

int main(int argc, char *argv[]) {
    int n, a[20][20];
    cout << "n = "; cin >> n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout<< "a[" << i << "][" << j <<"] = ";
            cin >> a[i][j];
        }
    }

    //a[n - 1][0] = 1;

    for (int i = n - 1; i > -1; i--) {
        for (int j = 0; j < n; j++) {
            if ((i == n - 1) && (j == 0)) continue;
            if (i == n - 1) {
                a[i][j] += a[i][j - 1];
            }
            else if (j == 0) {
                a[i][j] += a[i + 1][j];
            } else {
                a[i][j] += max(a[i][j - 1], a[i + 1][j], a[i + 1][j - 1]);
            }
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) cout << a[i][j] << " ";
        cout << endl;
    }
    return 0;
}
