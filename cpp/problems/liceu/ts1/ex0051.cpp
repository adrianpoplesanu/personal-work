// TS1 e5 p110 pdf
#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
    float x;
    cout << "x = "; cin >> x;
    if (x < 5) cout << x * x - 3 << endl;
    else if (x <= 25) cout << x + 1 << endl;
         else cout << x * x - 5 * x + 6 << endl;
    return 0;
}
