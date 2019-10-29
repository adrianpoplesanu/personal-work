// TS1 e32 p113 pdf
#include <iostream>
using namespace std;

int func(int a, int b, int c, int n) {
    if (n == 1) return -b/a;
    if (n == 2) return (b*b)/(a*a) - 2 * c / a;
    return -b/a * func(a, b, c, n - 1) - c/a * func(a, b, c, n -2);
}

int main(int argc, char *argv[]) {
    int a, b, c, n;
    cout << "a = "; cin >> a;
    cout << "b = "; cin >> b;
    cout << "c = "; cin >> c;
    cout << "n = "; cin >> n;
    cout << func(a, b, c, n) << endl;
    return 0;
}
