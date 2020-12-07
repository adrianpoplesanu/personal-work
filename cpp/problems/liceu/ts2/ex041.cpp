// ts2 p23 e1
#include <iostream>
using namespace std;

int main (int argc, char *argv[]) {
    int a[10], n;
    cout << "n = "; cin >> n;
    for (int i = 0; i < n; i++) {
        cout << "a[" << i << "] = "; cin >> a[i];
    }

    for (int i = 0; i < n - 1; i++) {
        for (int j = i; j < n; j++) {
            if (a[i] > a[j]) {
                int aux = a[i];
                a[i] = a[j];
                a[j] = aux;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        cout << a[i] << " ";
    }
    cout << "\n";
    return 0;
}
