// TS1 e1 p123 pdf
#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
    int n, a[30];
    bool distincte = true;
    cout << "n = "; cin >> n;
    for (int i = 0; i < n; i++) {
        cout << "a[" << i << "] = "; cin >> a[i];
    }
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (a[i] == a[j]) distincte = false;
        }
    }
    if (distincte) cout << "distincte" << endl;
    else cout << "NEdistincte" << endl;
    return 0;
}
