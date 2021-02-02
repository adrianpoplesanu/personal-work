// ts2 p47 e20
#include <iostream>
using namespace std;

int horner(int a[10], int n, int x) {
    int rez = a[0];
    for (int i = 0; i < n - 1; i++) {
        rez = rez * x + a[i + 1];
    }
    return rez;
}

int main(int argc, char *argv[]) {
    int a[10] = {1, 5, 6, 2}, n = 4; // 64 + 80 + 24 + 2 = 170
    int x = 4;
    cout << horner(a, n, x) << "\n";
    return 0;
}
