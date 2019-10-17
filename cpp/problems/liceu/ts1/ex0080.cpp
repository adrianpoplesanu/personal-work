// TS1 e28 p112 pdf
#include <iostream>
using namespace std;

bool prim(int n) {
    for (int i = 2; i < n; i++) if (n % i == 0) return false;
    return true;
}

int main(int argc, char *argv[]) {
    int n;
    cout << "n = "; cin >> n;
    for (int i = 2; i <= n / 2; i++) {
        if (prim(i) && prim(n-i)) {
            cout << i << " + " << n -i << endl;
        }
    }
    return 0;
}
