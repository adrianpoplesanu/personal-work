// TS1 e1 pg131 pdf v2
#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
    int n, a[10];
    cout << "n = "; cin >> n;
    for (int i = 0; i < n; i++) {
        cout << "a[" << i << "] = "; cin >> a[i];
    }
    for (int i = n - 1; i >= 0; i--) {
        int max = a[i], poz = i, aux;
        for (int j = i; j >= 0; j--) {
            if (max < a[j]) {
                max = a[j];
                poz = j;
            }
        }
        aux = a[i];
        a[i] = a[poz];
        a[poz] = aux;
    }
    for (int i = 0; i < n; i++) cout << a[i] << " ";
    cout << endl;
    return 0;
}
