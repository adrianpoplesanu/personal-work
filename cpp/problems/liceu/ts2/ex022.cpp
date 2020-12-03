// ts2 p17 e1
#include <iostream>
using namespace std;

int main (int argc, char *argv[]) {
    int a = 7; int &b = a;
    cout << a << " " << &a << "\n";
    cout << b << " " << &b << "\n";
    return 0;
}
