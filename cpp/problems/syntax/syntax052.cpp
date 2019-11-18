#include <iostream>
using namespace std;

void baza2(int n) {
    int c = n % 2;
    if (n > 0) {
        baza2(n/2);
        cout << c;
    }
    //cout << c;
}

int main(int argc, char *argv[]) {
    int a = 1;
    //cout << (a & 1023);
    baza2(1); cout << endl;
    baza2(2); cout << endl;
    baza2(3); cout << endl;
    baza2(4); cout << endl;
    baza2(5); cout << endl;
    baza2(6); cout << endl;
    baza2(7); cout << endl;
    return 0;
}
