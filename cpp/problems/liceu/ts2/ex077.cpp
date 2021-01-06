// ts2 p45 e1
#include <iostream>
using namespace std;

float calculate(float x) {
    return (x - (int)x) * 10;
}

int main(int argc, char *argv[]) {
    float x = 3.14;
    cout << calculate(x) << "\n";
    return 0;
}
