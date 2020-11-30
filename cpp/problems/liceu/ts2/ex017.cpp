// ts2 p15 e2
#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
    // int *a[3] = 3 elemente de tip int*
    // int (*a)[3] = oricate elemente de tip int[3]

    float *a[3], b[3], c;

    a[1] = b;
    a[0] = &c;

    return 0;
}
