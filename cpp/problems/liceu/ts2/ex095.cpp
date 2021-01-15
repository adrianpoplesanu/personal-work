// ts2 p47 e17
#include <iostream>
using namespace std;

void merge(int a[10], int b[10], int c[20], int n, int m) {
    int i = 0, j = 0, k = 0;
    while(i < n && j < m) {
        if (a[i] < b[j]) c[k++] = a[i++];
        else c[k++] = b[j++];
    }
    while(i < n) c[k++] = a[i++];
    while(j < m) c[k++] = b[j++];
}

int main(int argc, char *argv[]) {
    int a[10] = {2, 6, 8}, b[10] = {1, 3, 4, 7, 9}, c[20], n = 3, m = 5;
    merge(a, b, c, n, m);
    for (int i = 0; i < n + m; i++) {
        cout << c[i] << " ";
    }
    cout << "\n";
    return 0;
}
