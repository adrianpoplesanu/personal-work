// ts2 p46 e7 ver b
#include <iostream>
using namespace std;

long invers(long n) {
    long inv = 0;
    while(n) {
        int r = n % 10;
        n /= 10;
        inv *= 10;
        inv += r;
    }
    return inv;
}

int main(int argc, char *argv[]) {
    long n, m;
    cout << "n = "; cin >> n;
    cout << "m = "; cin >> m;
    for (long i = n; i < m; i++) cout << invers(i) << "\n";
    return 0;
}
