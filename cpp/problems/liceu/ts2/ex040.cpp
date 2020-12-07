// ts2 p23 e1
#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
    int a[10], n;
    cout << "n = "; cin >> n;
    for (int i = 0; i < n; i++) {
        cout << "a[" << i << "] = "; cin >> a[i];
    }
    int sortat = 0;
    while (!sortat) {
        sortat = 1;
        for (int i = 0; i < n - 1; i++) {
            if (a[i] > a[i + 1]) {
                int aux = a[i];
                a[i] = a[i + 1];
                a[i + 1] = aux;
                sortat = 0;
            }
        }
    }
    for (int i = 0; i < n; i++) {
        cout << a[i] << " ";
    }
    cout << "\n";
    return 0;
}
