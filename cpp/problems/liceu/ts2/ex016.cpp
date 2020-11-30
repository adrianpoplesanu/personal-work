// ts2 p15 e1
#include <iostream>
using namespace std;

int main (int argc, char *argv[]) {
    int a = 7, *b = &a;
    cout << b[0] << "\n";
    cout << *b << "\n";
    return 0;
}
