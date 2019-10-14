// TS1 e24 p112
#include <iostream>
using namespace std;

int suma_divizorilor(int n) {
    int suma = 0;
    for (int i = 1; i < n; i++) {
        if (n % i == 0) suma += i;
    }
    return suma;
}

int main(int argc, char *argv[]) {
    int n;
    cout << "n = "; cin >> n;
    for (int i = 1; i <= n; i++) {
        if (i == suma_divizorilor(i)) cout << i << " ";
    }
    cout << endl;
    return 0;
}
