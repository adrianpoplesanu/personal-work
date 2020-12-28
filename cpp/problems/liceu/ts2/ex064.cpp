// ts2 p37 e2
#include <iostream>
using namespace std;

int cmmdc(int a, int b) {
    while(a != b) {
       if (a > b) a -= b;
       else b -= a;
    }
    return a;
}

int main(int argc, char *argv[]) {
    int n, a[100];
    cout << "n = "; cin >> n;
    for (int i = 0; i < n; i++) {
        cout << "a[" << i << "] = "; cin >> a[i];
    }
    int c = a[0];
    for (int i = 1; i < n; i++) {
        c = cmmdc(c, a[i]);
    }
    cout << c << "\n";
    return 0;
}
