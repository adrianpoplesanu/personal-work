// ts2 p46 e10
#include <iostream>
using namespace std;

void read(int a[100][100], string identifier, int m, int n) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cout << identifier << "[" << i << "][" << j << "] = "; cin >> a[i][j];
        }
    }
}

void write(int a[100][100], int m, int n) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cout << a[i][j] << " ";
        }
        cout << "\n";
    }
}

void add(int a[100][100], int b[100][100], int c[100][100], int m, int n) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            c[i][j] = a[i][j] + b[i][j];
        }
    }
}

int main(int argc, char *argv[]) {
    int a[100][100], b[100][100], c[100][100], m, n;
    cout << "m = "; cin >> m;
    cout << "n = "; cin >> n;
    read(a, "a", m, n);
    read(b, "b", m, n);
    add(a, b, c, m, n);
    write(c, m, n);
    return 0;
}
