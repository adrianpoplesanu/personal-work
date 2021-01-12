// ts2 p47 e14
#include <iostream>
using namespace std;

void read(int a[100][100], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << "a[" << i << "][" << j << "] = "; cin >> a[i][j];
        }
    }
}

void switch_line(int a[100][100], int n, int l1, int l2) {
    for (int i = 0; i < n; i++) {
        int aux = a[l1][i];
        a[l1][i] = a[l2][i];
        a[l2][i] = aux;
    }
}

void display(int a[100][100], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) cout << a[i][j] << " ";
        cout << "\n";
    }
}

int main(int argc, char *argv[]) {
    int a[100][100], n, l1, l2;
    cout << "n = "; cin >> n;
    read(a, n);
    cout << "l1 = "; cin >> l1;
    cout << "l2 = "; cin >> l2;
    switch_line(a, n, l1, l2);
    display(a, n);
    return 0;
}
