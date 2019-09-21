// TS1 e2 p163
#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
    float a, b, c, e;
    cout << "a = "; cin >> a;
    cout << "b = "; cin >> b;
    cout << "c = "; cin >> c;
    if (c > 0) e = a + b;
    else if (c == 0) e = a * b;
    else e = a - b;
    cout << "e = " << e << endl;
    return 0;
}
