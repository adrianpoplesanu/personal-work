#include <iostream>
using namespace std;

float discretizer(float value) {
    int div = (int)(value / 0.125);
    return div * 0.125;
}

int main(int argc, char *argv[]) {
    cout << discretizer(0.433) << "\n";
    cout << discretizer(0.458) << "\n";
    cout << discretizer(0.469) << "\n";
    cout << discretizer(0.472) << "\n";
    cout << discretizer(0.479) << "\n";
    cout << discretizer(0.499) << "\n";
    cout << discretizer(0.501) << "\n";
    return 0;
}
