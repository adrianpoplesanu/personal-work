// TS1 e3 p110 pdf
#include <iostream>
#include <math.h>
using namespace std;

int main(int argc, char *arg[]) {
    float a, b, c;
    cout << "a = "; cin >> a;
    cout << "b = "; cin >> b;
    cout << "c = "; cin >> c;
    float delta = b * b - 4 * a * c;
    if (a == 0) {
        cout << "{" << -c / b << "}" << endl;
    } else if (delta > 0) {
        cout << "{" << (-b + sqrt(delta)) / (2 * a) << ", " << (-b - sqrt(delta)) / (2 * a) << "}"<< endl;
    } else {
        cout << "delta negativ, nu merge, sunt numere imaginare" << endl;
    }
    return 0;
}
