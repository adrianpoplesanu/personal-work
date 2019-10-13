// TS1 e21 p111 pdf
#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
    float x;
    cout << "x = "; cin >> x;
    cout << ((int(x * 100000000) / 100) % 10000) * 0.0001 << endl;
    return 0;
}
