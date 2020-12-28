// ts2 p38 e2
#include <iostream>
using namespace std;

bool palindrom_check(int n) {
    int orig = n, inv = 0, r;
    while (orig != 0) {
        r = orig % 10;
        orig /= 10;
        inv *= 10;
        inv += r;
    }
    return n == inv;
}

int main(int argc, char *argv[]) {
    int n, m;
    cout << "n = "; cin >> n;
    cout << "m = "; cin >> m;
    for (int i = n; i <= m; ++i) {
        if (palindrom_check(i) && palindrom_check(i * i)) cout << i << "\n";
    }
    return 0;
}
