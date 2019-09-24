// TS1 e1 p164
#include <iostream>
using namespace std;

int main(int argc, char* argv[]) {
    float a, b, x;
    cout << "a = "; cin >> a;
    cout << "b = "; cin >> b;
    if (a) {
        x = -b/a;
        cout << "x = " << x << endl;
    } else {
        if (b == 0) cout << "infinitate solutii" << endl;
        else cout << "nu are solutie. impartire la zero" << endl;
    }
    return 0;
}
