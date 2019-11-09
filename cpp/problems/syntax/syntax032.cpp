#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
    int a = 1;
    a = a << 8;
    cout << a << endl;
    a += (1 << 4);
    cout << (a & 0xFF) << endl;
    a += (1 << 6);
    cout << (a & 0xFF) << endl;
    return 0;
}
