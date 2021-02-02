// ts2 p47 e19
#include <iostream>
using namespace std;

void add(int a[10], int b[10], int c[10], int n, int m) {
    for (int i = 0; i < (n > m ? n : m); i++) {
        c[i] = a[i] + b[i];
    }
}

void multiply(int a[10], int b[10], int d[10], int n, int m) {
    for(int i = 0; i < n + m; i++) d[i] = 0;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            d[i + j] += a[i] * b[j];
        }
    }
}

void display(int a[10], int n) {
    for(int i = 0; i < n; i++) cout << a[i] << " ";
    cout << "\n";
}

int main (int argc, char *argv[]) {
    int a[10] = {1, 2, 3, 4}, b[10] = {2, 2, 3}, c[10], d[10], n = 4, m = 3;
    add(a, b, c, n, m);
    display(c, n > m ? n : m);
    multiply(a, b, d, n, m);
    display(d, n + m - 1);
    return 0;
}
