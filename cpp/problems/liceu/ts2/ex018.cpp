// ts2 p16 e2
#include <iostream>
using namespace std;

int main (int argc, char *argv[]) {
    float (*a)[3], c[3], d[7][3];
    a = d;
    a = &c;
    return 0;
}
