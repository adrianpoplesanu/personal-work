// TS1 e34 p113 pdf
#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
    int n, p, a, i = 0, k = 0;
    cout << "n = "; cin >> n;
    cout << "p = "; cin >> p;
    while(i++ < n) {
        cout << "a[" << i << "] = "; cin >> a;
        while (a % p == 0) {
            a /= p;
            k++;
        }
    }
    cout << "k = " << k << endl;
    return 0;
}
