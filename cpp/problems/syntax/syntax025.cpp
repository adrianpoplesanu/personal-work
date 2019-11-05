#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
    int a = 1;
    cout << a << endl;
    cout << (a << 8) << endl;
    a = a << 8;
    cout << a << endl;
    return 0;
}
