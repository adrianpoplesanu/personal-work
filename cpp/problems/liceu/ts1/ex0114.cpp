// TS1 e1 p140 pdf v3
#include <iostream>
using namespace std;

void declara_matricea(int **&a, int n, int m) {
    a = new int*[n];
    for (int i = 0; i < n; i++) a[i] = new int[m];
}

void citeste_matrice(int **&a, int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << "a[" << i << "," << j << "] = "; cin >> a[i][j];
        }
    }
}

void afiseaza_matrice(int **a, int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) cout << a[i][j] << " ";
        cout << endl;
    }
}

void interschimba_linii(int **&a, int n, int m, int l1, int l2) {
    for (int i = 0; i < m; i++) {
        int aux = a[l1][i];
        a[l1][i] = a[l2][i];
        a[l2][i] = aux;
    }
}

int main(int argc, char *argv[]) {
    int **a, n, m, l1, l2;
    cout << "n = "; cin >> n;
    cout << "m = "; cin >> m;
    // lines moved to declara_matricea:
    // a = new int*[n];
    // for (int i = 0; i < n; i++) a[i] = new int[m];
    declara_matricea(a, n, m);
    citeste_matrice(a, n, m);
    afiseaza_matrice(a, n, m);
    cout << "l1 = "; cin >> l1;
    cout << "l2 = "; cin >> l2;
    interschimba_linii(a, n, m, l1, l2);
    afiseaza_matrice(a, n, m);
    return 0;
}
