// TS1 e7 p105 pdf v2
#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
    int n, inv;
    cout << "n = "; cin >> n;
    for(inv = 0; n; ) {
        inv = inv * 10 + n % 10;
        n /= 10;
    }
    cout << "inv = " << inv << endl;
    return 0;
}
