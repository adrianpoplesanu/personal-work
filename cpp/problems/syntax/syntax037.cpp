#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
    int a = 0xA;
    cout << a << endl;
    for (int i = 0; i < 50; i++) {
        cout << (i & a) << endl;
    }
    return 0;
}
