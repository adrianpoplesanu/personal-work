// TS1 e1 pg161
#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
    int a, b, c;
    cout << "a = "; cin >> a;
    cout << "b = "; cin >> b;
    c = a;
    a = b;
    b = c;
    cout << "a = " << a << endl;
    cout << "b = " << b << endl;
    return 0;
}
