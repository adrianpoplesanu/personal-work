// TS1 e18 p111 pdf v2
#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
    int n, s = 0, p = 1;
    cout << "n = "; cin >> n;
    for (int i = 2; i < n; i++) {
        if (n % i == 0) {
            bool prim = true;
            for(int k = 2; k < i; k++) if (i % k == 0) { prim = false; break; }
            if (prim) {
                s += i;
                p *= i;
            }
        }
    }
    cout << "s = " << s << endl;
    cout << "p = " << p << endl;
    return 0;
}
