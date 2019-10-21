// TS1 e31 p113 pdf v2
#include <iostream>
using namespace std;

int cmmdc(int a, int b) {
    if (a > b) return cmmdc(a - b, b);
    if (a < b) return cmmdc(a, b - a);
    return a;
}

int main(int argc, char *argv[]) {
    int n, temp;
    cout << "n = "; cin >> n;
    if (n < 2) {
        cout << "cmmdc for less than 2 numbers ?!?";
        return 1;
    }
    int a, b;
    cout << "a[" << 0 << "] = "; cin >> a;
    cout << "a[" << 1 << "] = "; cin >> b;
    temp = cmmdc(a, b);
    for (int i = 2; i < n; i++) {
        cout << "a[" << i + 1 << "] = "; cin >> a;
        temp = cmmdc(temp, a);
    }
    cout << "cmmdc = " << temp << endl;
    return 0;
}
