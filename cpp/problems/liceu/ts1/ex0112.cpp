// TS1 e1 p140 pdf
#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
    int a[10][10], n, m, l1, l2;
    cout << "n = "; cin >> n;
    cout << "m = "; cin >> m;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << "a[" << i << ", " << j << "] = "; cin >> a[i][j];
        }
    }
    cout << "l1 = "; cin >> l1;
    cout << "l2 = "; cin >> l2;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) cout << a[i][j] << " ";
        cout << endl;
    }
    for (int i = 0; i < m; i++) {
        int aux = a[l1][i];
        a[l1][i] = a[l2][i];
        a[l2][i] = aux;
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) cout << a[i][j] << " ";
        cout << endl;
    }
    return 0;
}
