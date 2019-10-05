// TS1 e10 p110 pdf
#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
    int n, i, p, k, total = 0;
    cout << "n = "; cin >> n;
    cout << "p = "; cin >> p;
    cout << "k = "; cin >> k;
    while(n--) {
        cout << "i = "; cin >> i;
        if (i % p == k) total++;
    }
    cout << "total = " << total << endl;
    return 0;
}
