// TS1 e2 p132 pdf
#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
    int a[10], n, gasit;
    cout << "n = "; cin >> n;
    for (int i = 0; i < n; i++) {
        cout << "a[" << i << "] = "; cin >> a[i];
    }
    do {
        gasit = 0;
        for (int i = 0; i < n - 1; i++) {
            for (int j = i + 1; j < n; j++)
                if (a[i] > a[j]) {
                    int aux = a[i];
                    a[i] = a[j];
                    a[j] = aux;
                    gasit = 1;
                }
        }
    } while (gasit);
    for (int i = 0; i < n; i++) cout << a[i] << " ";
    cout << endl;
    return 0;
}
