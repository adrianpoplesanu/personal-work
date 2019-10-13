// TS1 e20 p111 pdf
#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
    int n;
    cout << "n = "; cin >> n;
    n = (n / 1000) * 100 + n % 100;
    cout << "n = " << n << endl;
    return 0;
}
