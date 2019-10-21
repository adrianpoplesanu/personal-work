// TS1 e31 p113 pdf
#include <iostream>
using namespace std;

bool prim(int n) {
    for(int i = 2; i < n; i++) if (n % i == 0) return false;
    return true;
}

bool is_divisible(int a[], int n, int f) {
    for (int i = 0; i < n; i++) if (a[i] % f != 0) return false;
    return true;
}

void actual_divide(int a[], int n, int f) {
    for (int i = 0; i < n; i++) a[i] /= f;
}

/*int cmmdc(int a, int b) {
    if (a > b) return cmmdc(a - b, b);
    if (a < b) return cmmdc(a, b - a);
    return a;
}*/

int main(int argc, char *argv[]) {
    int n, max = 0, prod = 1;
    cout << "n = "; cin >> n;
    int a[n];
    for (int i = 0; i < n; i++) {
        cout << "a[" << i << "] = "; cin >> a[i];
        if (max < a[i]) max = a[i];
    }
    for (int i = 2; i < max; ) {
        if (prim(i)) {
            if (is_divisible(a, n, i)) {
                prod *= i;
                actual_divide(a, n, i);
            } else {
                i++;
            }
        } else i++;
    }
    cout << "cmmdc = " << prod << endl;
    return 0;
}
