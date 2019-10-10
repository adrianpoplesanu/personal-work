// TS1 e17 p111 pdf
#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
    int n, tot = 0;
    cout << "n = "; cin >> n;
    while (n) {
        n /= 10;
        tot++;
    }
    cout << "tot = " << tot << endl;
    return 0;
}
