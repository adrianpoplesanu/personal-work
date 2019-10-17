// TS1 e30 p112 pdf
#include <iostream>
using namespace std;

int prod2(int a, int n) {
    if (n == 0) return 1;
    if (n % 2 == 0) {
        return prod2(a * a, n / 2);
    } else {
        return a * prod2(a, n - 1);
    }
}

int main(int argc, char *argv[]) {
    int a, n;
    cout << "a = "; cin >> a;
    cout << "n = "; cin >> n;
    cout << "prod2(" << a << ", " << n <<") = " << prod2(a, n) << endl; 
    return 0;
}
