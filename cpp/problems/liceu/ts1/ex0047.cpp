// TS1 e2 p110 pdf
#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
    float a, b, c;
    cout << "a = "; cin >> a;
    cout << "b = "; cin >> b;
    cout << "c = "; cin >> c;
    if (a*a == b*b + c*c || b*b == a*a + c*c || c*c == a*a + b*b) cout << "e triunghi dreptunghic" << endl;
    else cout << "nu e triunghi dreptunghic" << endl;
    return 0;
}
