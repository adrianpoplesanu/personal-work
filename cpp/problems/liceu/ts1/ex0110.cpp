#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
    int a[10], b[10], c[20], n, m;
    cout << "n = "; cin >> n;
    for (int i = 0; i < n; i++) {
        cout << "a[" << i << "] = "; cin >> a[i];
    }
    cout << "m = "; cin >> m;
    for (int j = 0; j < m; j++) {
        cout << "b[" << j << "] = "; cin >> b[j];
    }
    int i = 0, j = 0, k = 0;
    while (i < n && j < m) {
        if (a[i] < b[j]) {
            c[k++] = a[i++];
        } else {
            c[k++] = b[j++];
        }
    }
    while (i < n) {
        c[k++] = a[i++];
    }
    while (j < m) {
        c[k++] = b[j++];
    }
    for (int i = 0; i < k; i++) cout << c[i] << " ";
    cout << endl;
    return 0;
}
