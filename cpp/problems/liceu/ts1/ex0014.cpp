// TS1 e14 p132
#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
    int n, nr = 0;
    cout << "n = "; cin >> n;
    while (n) {
        n /= 10;
        nr++;
    }
    cout << "nr = " << nr << endl;
    return 0;
}
