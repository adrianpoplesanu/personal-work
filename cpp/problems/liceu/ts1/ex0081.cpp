// TS1 e29 p112 pdf
#include <iostream>
using namespace std;

bool is_cifra(int n, int c) {
    while (n) {
        int t = n % 10;
        n /= 10;
        if (t == c) return true;
    }
    return false;
}

int main(int argc, char *argv[]) {
    int n, m, suma = 0;
    cout << "n = "; cin >> n;
    cout << "m = "; cin >> m;
    while (n) {
       int c = n % 10;
       n /= 10;
       if (is_cifra(m, c)) suma++;
    }
    cout << "suma = " << suma << endl;
    return 0;
}
