// TS1 e3 p122 pdf
#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
    int n, m, a[30][30];
    cout << "n = "; cin >> n;
    cout << "m = "; cin >> m;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << "a[" << i << ", " << j <<"] = "; cin >> a[i][j];
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) cout << a[i][j] << " ";
        cout << endl;
    }
    return 0;
}
