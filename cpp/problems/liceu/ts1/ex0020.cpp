// TS1 e1 p163
#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
    int a, b, m;
    cout << "a = "; cin >> a;
    cout << "b = "; cin >> b;
    if (a < b) m = b;
    else m = a;
    cout << "m = " << m << endl;
    return 0;
}
