// TS1 e35 p113 pdf
#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
    int i, n, k, s = 0;
    cout << "n = "; cin >> n;
    cout << "k = "; cin >> k;
    if (k*(k+1) / 2 > n) {
        cout << "IMPOSSIBRU!" << endl;
        return -1;
    }
    for (i = 1; i < n; i++) {
        k--;
        if (k == 0) break;
        cout << i << " ";
        s += i;
    }
    if (n - s > 0) cout << n - s;
    cout << endl;
    return 0;
}
