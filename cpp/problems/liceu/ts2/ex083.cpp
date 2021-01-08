// ts2 p46 e7
#include <iostream>
using namespace std;

void invers(long n) {
    while(n) {
        int r = n % 10;
        n /= 10;
        cout << r;
    }
    cout << "\n";
}

int main(int argc, char *argv[]) {
    long n, m;
    cout << "n = "; cin >> n;
    cout << "m = "; cin >> m;
    for (long i = n; i < m; i++) invers(i);
    return 0;
}
