// TS1 e5 p170
#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
    int n, s = 0, p = 1;
    cout << "n = "; cin >> n;
    for (int i = 1; i <= n; i++) {
        p *= i;
        s += p;
    }
    cout << "s = " << s << endl;
    return 0;
}
