// TS e5 p127 pdf
#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
    int a[30], b[30], n, m;
    cout << "n = "; cin >> n;
    for (int i = 0; i < n; i++) {
        cout << "a[" << i << "] = "; cin >> a[i];
    }
    cout << "m = "; cin >> m;
    for (int i = 0; i < m; i++) {
        cout << "b[" << i << "] = "; cin >> b[i];
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) cout << "(" << a[i] << ", " << b[j] << ")" << endl;
    }
    return 0;
}
