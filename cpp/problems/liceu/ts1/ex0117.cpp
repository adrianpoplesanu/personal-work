// TS1 e1 p143 pdf v2
#include <iostream>
using namespace std;

void initializeaza_vector(int *&a, int n) {
    a = new int[n];
}

void citeste_vector(int *&a, int n) {
    for (int i = 0; i < n; i++) {
        cout << "a[" << i << "] = "; cin >> a[i];
    }
}

void afiseaza_vector(int *a, int n) {
    for (int i = 0; i < n; i++) cout << a[i] << " ";
    cout << endl;
}

int main(int argc, char *argv[]) {
    int *a, n;
    cout << "n = "; cin >> n;
    initializeaza_vector(a, n);
    citeste_vector(a, n);
    afiseaza_vector(a, n);
    return 0;
}
