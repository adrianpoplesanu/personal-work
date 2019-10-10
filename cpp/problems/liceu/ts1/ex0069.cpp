// TS1 e18 p111 pdf
#include <iostream>
using namespace std;

bool prim(int k) {
    for (int i = 2; i < k; i++) if (k % i == 0) return false;
    return true;
}

int main(int argc, char *argv[]) {
    int n, s = 0, p = 1;
    cout << "n = "; cin >> n;
    for(int i = 2; i < n; i++) {
        if (prim(i) && n % i == 0) {
            s += i;
            p *= i;
        }
    }
    cout << "s = " << s << endl;
    cout << "p = " << p << endl;
    return 0;
}
