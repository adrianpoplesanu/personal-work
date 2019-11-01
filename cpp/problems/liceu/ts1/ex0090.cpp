// TS1 e37 p114 pdf
#include <iostream>
using namespace std;

int min(int a, int b) {
    if (a < b) return a;
    return b;
}

int main(int argc, char *argv[]) {
    int m, n, s = 0;
    cout << "n = "; cin >> n;
    cout << "m = "; cin >> m;
    for (int i = 1; i < min(m, n); i++) {
        s += i * (m - i) * (n - i);
    }
    cout << "s = " << s << endl;
    return 0;
}
