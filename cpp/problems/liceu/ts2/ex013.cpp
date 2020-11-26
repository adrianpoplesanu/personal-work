// ts2 p12 e1
#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
    float a[10], *b;
    a[7] = 3;
    b = a;
    cout << b[7] << "\n";
    cout << 7[b] << "\n";
    return 0;
}
