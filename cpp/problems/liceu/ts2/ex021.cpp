// ts2 p16 e4
#include <iostream>
using namespace std;

int main (int argc, char *argv[]) {
    int (*a[3])[2][5], b[2][5], c[9][2][5];

    a[0] = &b;
    a[1] = c;
    return 0;
}
