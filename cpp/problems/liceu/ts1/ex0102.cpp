// TS1 e4 p125 pdf
#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
    int a[30], b[30], c[30], n, m, p = 0;
    cout << "n = "; cin >> n;
    for (int i = 0; i < n; i++) {
        cout << "a[" << i << "] = "; cin >> a[i];
    }
    cout << "m = "; cin >> m;
    for (int i = 0; i < m; i++) {
        cout << "b[" << i << "] = "; cin >> b[i];
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) if (a[i] == b[j]) c[p++] = a[i];
    }
    for (int i = 0; i < p; i++) cout << c[i] << " ";
    cout << endl;
    return 0;
}
