// ts2 p46 e5
#include <iostream>
#include <cmath>
using namespace std;

float ipotenuza(float a, float b) {
    return sqrt(a*a + b*b);
}

int main(int argc, char *argv[]) {
    float a, b;
    cout << "a = "; cin >> a;
    cout << "b = "; cin >> b;
    cout << ipotenuza(a, b) << "\n";
    return 0;
}
