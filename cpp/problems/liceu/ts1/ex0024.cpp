// TS1 e1 p 165
#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
    int n;
    cout << "n = "; cin >> n;
    switch(n) {
        case 1: cout << "e 1" << endl; break;
        case 2: cout << "e 2" << endl; break;
        default: cout << "e altceva" << endl;
    }
    return 0;
}
