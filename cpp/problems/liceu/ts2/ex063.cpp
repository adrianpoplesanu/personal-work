// ts2 p37 e1
#include <iostream>
using namespace std;

int cmmdc(int a, int b) {
    while(a != b) {
        if (a > b) a -= b;
        else b -= a;
    }
    return a;
}

int main(int argc, char *argv[]) {
    int a, b;
    cout << "a = "; cin >> a;
    cout << "b = "; cin >> b;
    cout << cmmdc(a, b) << "\n";
    return 0;
}
