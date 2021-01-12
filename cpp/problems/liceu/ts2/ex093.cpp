// ts2 p47 e15
#include <iostream>
using namespace std;

void read(int a[100][100], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << "a[" << i << "][" << j << "] = "; cin >> a[i][j];
        }
    }
}

void switch_columns(int a[100][100], int n, int c1, int c2) {
    for (int i = 0; i < n; i++) {
        int aux = a[i][c1];
        a[i][c1] = a[i][c2];
        a[i][c2] = aux;
    }
}

void display(int a[100][100], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) cout << a[i][j] << " ";
        cout << "\n";
    }
}

int main(int argc, char *argv[]) {
    int a[100][100], n, c1, c2;
    cout << "n = "; cin >> n;
    read(a, n);
    cout << "c1 = "; cin >> c1;
    cout << "c2 = "; cin >> c2;
    switch_columns(a, n, c1, c2);
    display(a, n);
    return 0;
}
