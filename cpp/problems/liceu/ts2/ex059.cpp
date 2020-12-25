// ts2 p35 e1
#include <iostream>
using namespace std;

void intersc(int &a, int &b) {
    int aux = a; a = b; b = aux;
}

int main(int argc, char *argv[]) {
    int x = 2, y = 3;
    intersc(x, y);
    cout << x << " " << y << '\n';
    return 0;
}
