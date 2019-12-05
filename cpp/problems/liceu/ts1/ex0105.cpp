// TS1 e1 pg131 pdf
#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
    int n, a[10];
    cout << "n = "; cin >> n;
    for (int i = 0; i < n; i++) {
        cout << "a[" << i << "] = "; cin >> a[i];
    }
    for (int i = 0; i < n; i++) {
        int min = a[i], poz = i;
        for (int j = i; j < n; j++) if (min > a[j]) {
            min = a[j];
            poz = j;
        }
        int aux = a[i];
        a[i] = a[poz];
        a[poz] = aux;
    }
    for (int i = 0; i < n; i++) cout << a[i] << " ";
    cout << endl;
    return 0;
}
