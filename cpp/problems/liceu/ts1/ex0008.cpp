// TS1 e8 p132
#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
    int n;
    cout << "n = "; cin >> n;
    for(int i = n - 1; i > 0; i--) {
        if ((i * i) <= n) {
            n -= (i * i);
        }
        if (n == 0) break;
    }
    if (n == 0) cout << "Suma de patrare" << endl;
    else cout << "NU e suma de patrate" << endl;
    return 0;
}
