// TS1 e6 p110 pdf - incomplet
#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
    float a, b, c;
    cout << "a = "; cin >> a;
    cout << "b = "; cin >> b;
    cout << "c = "; cin >> c;
    if (a == 0) {
        cout << "e doar o solutie reala ";
        if(-b/c >= 0) cout << "pozitiva";
        else cout << "negativa";
    } else {
        float delta = b * b - 4 * a * c;
        if (delta < 0) {
            cout << "solutiile sunt imaginare";
        } else if (delta == 0) {
            cout << "ecuatia are o singura solutie reala";
        } else {
            cout << "solutiile sunt reale";
        }
    }
    cout << endl;
    return 0;
}
