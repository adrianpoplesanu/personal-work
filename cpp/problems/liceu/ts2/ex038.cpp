// ts2 p21 e1
#include <iostream>
using namespace std;

float suma1 (int n) {
    float s = 0.0f;
    for(int i = 1; i < n; i++) s += 1.0f / i;
    return s;
}

int main (int argc, char *argv[]) {
    cout << suma1 (2) << "\n";
    cout << suma1 (3) << "\n";
    cout << suma1 (4) << "\n";
    cout << suma1 (5) << "\n";
    cout << suma1 (6) << "\n";
    cout << suma1 (7) << "\n";
    cout << suma1 (8) << "\n";
    cout << suma1 (9) << "\n";
    return 0;
}
