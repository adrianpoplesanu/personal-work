// ts2 p38 e1
#include <iostream>
using namespace std;

void palindrom_check(int n) {
    int orig = n, inv = 0, r;
    while (orig != 0) {
        r = orig % 10;
        orig /= 10;
        inv *= 10;
        inv += r;
    }
    if (n == inv) cout << n << "\n";
}

int main(int argc, char *argv[]) {
    int n, m;
    cout << "n = "; cin >> n;
    cout << "m = "; cin >> m;
    for (int i = n; i <= m; ++i) {
        palindrom_check(i);
    }
    return 0;
}
