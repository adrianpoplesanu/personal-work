// TS1 e2 p121 pdf
#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
    int n;
    float a[30], b[30];
    cout << "n = "; cin >> n;
    for (int i = 0; i  < n; i++) {
        cout << "a[" << i + 1 << "] = "; cin >> a[i];
    }
    for (int i = 0; i < n; i++) b[i] = a[i];
    for (int i = 0; i < n; i++) cout << b[i] << " ";
    cout << endl;
    return 0;
}
