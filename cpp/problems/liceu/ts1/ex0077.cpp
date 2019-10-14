// TS1 e25 p122 pdf
#include <iostream>
using namespace std;

int suma_patrate_cifre(int n) {
    int suma = 0;
    while (n) {
        int r = n % 10;
        suma += r * r;
        n /= 10;
    }
    return suma;
}

int main(int argc, char *argv[]) {
    int n;
    cout << "n = "; cin >> n;
    for (int i = 0; i < n; i++) {
        if (i == suma_patrate_cifre(i)) cout << i << " ";
    }
    cout << endl;
    return 0;
}
