// ts2 p21 e2
#include <iostream>
using namespace std;

float suma1 (int n) {
    float s = 0.0f;
    for(int i = 1; i <= n; i++) s += 1.0f / i;
    return s;
}

float suma2 (int n) {
    float sum = suma1(n);
    float prod = 1.0f;
    for (int i = 1; i <= n; i++) {
        prod *= sum;
    }
    return prod;
}

int main (int argc, char *argv[]) {
    cout << suma2 (2) << "\n";
    cout << suma2 (3) << "\n";
    cout << suma2 (4) << "\n";
    cout << suma2 (5) << "\n";
    cout << suma2 (6) << "\n";
    cout << suma2 (7) << "\n";
    cout << suma2 (8) << "\n";
    cout << suma2 (9) << "\n";
    return 0;
}
