// ts2 p16 e5
#include <iostream>
using namespace std;

int main (int argc, char *argv[]) {
    int *(*a)[3], *b[9][3];

    a = b;
    a = &b[5];

    return 0;
}
