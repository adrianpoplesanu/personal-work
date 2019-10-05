// ts1 e11 pdf v3
#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
    int n, p = 1;
    float e = 1;
    cout << "n = "; cin >> n;
    for (int i = 1; i <= n; i++) {
        p *= i;
        e += float(1) / p;
    }
    cout << "e3 = " << e << endl;
    return 0;
}
