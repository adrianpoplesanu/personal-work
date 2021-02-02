// ts2 p48 e21
#include <iostream>
using namespace std;

float func(float x) {
    return 2.1 * x + 1.4;
}

int main(int argc, char *argv[]) {
    float a = 1.6, b = 5.2;
    int n = 10;
    for(float i = 0; i < n; i++) {
        cout << func(a + (b - a) / (float)n * i ) << " ";
    }
    cout << "\n";
    return 0;
}
