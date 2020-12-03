// ts2 p16 e3
#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
    float *a[3][2], c[33], d[7][23], e;
    a[0][0] = &e;
    a[1][1] = c;
    a[1][0] = &c[0];
    a[2][0] = &d[6][2];
    a[3][1] = d[3];
    return 0;
}
