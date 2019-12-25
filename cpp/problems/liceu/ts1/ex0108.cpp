// TS1 e2 p133 pdf v2 - bubble sort
#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
    int a[10], n;
    cout << "n = "; cin >> n;
    for (int i = 0; i < n; i++) {
        cout << "a[" << i << "] = "; cin >> a[i];
    }
    bool sortat = false;
    while (!sortat) {
        sortat = true;
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (a[i] > a[j]) {
                    int aux = a[i];
                    a[i] = a[j];
                    a[j] = aux;
                    sortat = false;
                }
            }
        }
    }
    for (int i = 0; i < n; i++) cout << a[i] << " ";
    cout << endl;
    return 0;
}
