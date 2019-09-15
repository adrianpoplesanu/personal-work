// TS1 ex 5 pg 132
#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
    float x;
    cout << "x = "; cin >> x;
    if (x <= 10) cout << x * x + x - 2 << endl;
    else if (x <= 20) cout << 1/x << endl;
    else cout << (x - 1) / (x + 1) << endl;
    return 0;
}
