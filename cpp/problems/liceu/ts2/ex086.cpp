// ts2 p46 e9
#include <iostream>
using namespace std;

int last_digit(int n) {
    return n % 10;
}

int main(int argc, char *argv[]) {
    int n, suma = 0, produs = 1, factor = 1, x[100];
    cout << "n = "; cin >> n;
    for (int i = 0; i < n; i++) {
        cout << "x" << i << " = "; cin >> x[i];
    }
    for (int i = 0; i < n; i++) suma += x[i], suma=last_digit(suma);
    for (int i = 1; i < n; i++) factor *= x[i];
    for (int i = 0; i <= factor; i++) produs *= x[0], produs=last_digit(produs);
    cout << suma << "\n" << produs << "\n";
    return 0;
}
