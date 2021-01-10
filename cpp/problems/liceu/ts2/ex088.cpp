// ts2 p47 e11
#include <iostream>
using namespace std;

void adauga_coeficient(int x[100], int k) {
    if (k == 1) {
        x[0] = 1; x[1] = 1; x[2] = 0;
    } else {
        x[k + 1] = 0;
        for (int j = k + 1; j > 0; j--) {
            x[j] = x[j] + x[j - 1];
        }
    }
}

int main(int argc, char *argv[]) {
    int n, x[100];
    cout << "n = "; cin >> n;
    for (int i = 0; i < n; i++) {
        adauga_coeficient(x, i + 1);
    }
    for (int i = 0; i <= n; i++) cout << x[i] << " ";
    cout << "\n";
    return 0;
}
