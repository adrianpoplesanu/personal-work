// ts2 p47 e13
#include <iostream>
using namespace std;

int suma_cifrelor(int n) {
    int suma = 0;
    while(n) {
        suma += n % 10;
        n /= 10;
    }
    return suma;
}

int main(int argc, char *argv[]) {
    int n, m;
    cout << "n = "; cin >> n;
    cout << "m = "; cin >> m;
    for (int i = n; i <= m; i++) if (i % suma_cifrelor(i) == 0) cout << i << " ";
    cout << "\n";
    return 0;
}
