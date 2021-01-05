// ts2 p45 e1
#include <iostream>
#include <cmath>
using namespace std;

float calculate(float x) {
    return sin(x) + cos(x) * cos(2 * x);
}

int main(int argc, char *argv[]) {
    float x;
    cout << "x = "; cin >> x;
    cout << calculate(x) << "\n";
    return 0;
}
