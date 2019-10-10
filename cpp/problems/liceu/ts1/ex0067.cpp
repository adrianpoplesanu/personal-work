// TS1 e16 p111 pdf
#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
    int m, n;
    cout << "m = "; cin >> m;
    cout << "n = "; cin >> n;
    while (m != n) {
        if (m > n) m -= n;
        if (m < n) n -= m;
    }
    cout << "cmmdc = " << n << endl;
    return 0;
}
