// TS1 e16 p132
#include <iostream>
using namespace std;

bool prim(int n) {
    for (int i = 2; i < n - 1; i++) {
        if (n % i == 0) return false;
    }
    return true;
}

int main(int argc, char *argv[]) {
    float x;
    cout << "x = "; cin >> x;
    for (int i = (int)x; ; i--) {
        if (prim(i)) {
            cout << "p = " << i << endl;
            break;
        }
    }
    for (int i = (int) x + 1; ; i++) {
        if (prim(i)) {
            cout << "q = " << i << endl;
            break;
        }
    }
    return 0;
}
