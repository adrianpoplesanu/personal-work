#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
    int a = 0xF;
    cout << (60 & a) << endl;
    cout << (61 & a) << endl;
    cout << (62 & a) << endl;
    cout << (63 & a) << endl;
    cout << (64 & a) << endl;
    cout << (111 & a) << endl;
    return 0;
}
