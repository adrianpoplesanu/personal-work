// ts2 p14 e1
#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
    float G[7][8][3], (*A)[8][3], (*B)[3], *C;
    G[2][3][1] = 15;

    A = G; cout << A[2][3][1] << "\n";

    B = G[2]; cout << B[3][1] << "\n";

    C = G[2][3]; cout << C[1] << "\n";

    return 0;
}
