// ts2 p29 e3
#include <iostream>
using namespace std;

void t() {
    int b = 4;
    {
        int c = 3;
        cout << b << " " << c << "\n";
    }
}

int main (int argc, char *argv[]) {
    t();
    return 0;
}
