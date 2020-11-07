// TS2 p1 e2
#include <iostream>
using namespace std;

int main (int argc, char *argv[]) {
    int a = 7;
    int *adra = &a;
    int **adradra = &adra;
    cout << a << "\n" << adra << "\n" << adradra << "\n";
    return 0;
}
