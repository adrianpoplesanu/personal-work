// TS1 e1 p138 pdf
#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
    int a[10], n, val;
    cout << "n = "; cin >> n;
    for (int i = 0; i < n; i++) {
        cout << "a[" << i << "] = "; cin >> a[i];
    }
    cout << "val = "; cin >> val;
    int li = 0, ls = n;
    bool found = false;
    while (ls >= li) {
        int p = (li + ls) / 2; cout << p << endl;
        if (a[p] == val) {
            found = true;
            break;
        } else if (a[p] < val) {
            li = p + 1;
        } else {
            ls = p - 1;
        }
    }
    if (found) cout << "found" << endl;
    else cout << "not found" << endl;
    return 0;
}
