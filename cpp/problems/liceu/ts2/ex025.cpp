// ts2 p18 e3
#include <iostream>
using namespace std;

int main (int argc, char *argv[]) {
    float a = 121.65;
    int *lsb = (int*) &a; // asta e primul octet din float
    cout << (int)*lsb << "\n";
    return 0;
}
