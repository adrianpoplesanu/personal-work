// TS1 e1 p121 pdf
#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
    int n, a[30];
    cout << "n = "; cin >> n;
    for (int i = 0; i < n; i++) {
        cout << "a[" << i + 1 << "] = "; cin >> a[i];
    }
    for (int i = 0; i < n; i++) cout << a[i] << " ";
    cout << endl;
    return 0;
}
