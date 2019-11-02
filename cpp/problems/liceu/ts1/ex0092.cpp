// TS1 e40 p116 pdf
#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
    int n, p = 1;
    cout << "n = "; cin >> n;
    while (n--) {
        int a;
        cout << "a = "; cin >> a;
        p *= (1 + a);
    }
    cout << "p = " << p - 1 << endl;
    return 0;
}
