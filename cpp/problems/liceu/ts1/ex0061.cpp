// TS1 e12 p110 pdf
#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
    int c = 1, n = 0;
    cout << "c = 1" << endl;
    while (c != -1) {
        n *= 2;
        n += c;
        cout << "c = "; cin >> c;
    }
    cout << n << endl;
    return 0;
}
