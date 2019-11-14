// TS1 e1 p124 pdf
#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
    int n, a[30], e;
    bool found = false;
    cout << "n = "; cin >> n;
    for (int i = 0; i < n; i++) {
        cout << "a[" << i << "] = "; cin >> a[i];
    }
    cout << "e = "; cin >> e;
    for (int i = 0; i < n; i++) if (a[i] == e) found = true;
    if (found) cout << "found!" << endl;
    else cout << "not found!" << endl;
    return 0;
}
