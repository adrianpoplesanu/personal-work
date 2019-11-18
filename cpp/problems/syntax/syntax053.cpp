#include <iostream>
using namespace std;

void baza2(int n, int val) {
    int c = n % 2;
    if (n > 0) {
        //cout << c;
        if (c) cout << val;
        baza2(n/2, val + 1);
        //cout << c;
        //if (c) cout << val;
    }
    //cout << c;
}

int main(int argc, char *argv[]) {
    int a = 1;
    //cout << (a & 1023);
    //baza2(1); cout << endl;
    //baza2(2); cout << endl;
    //baza2(3); cout << endl;
    //baza2(4); cout << endl;
    baza2(4, 1); cout << endl;
    baza2(5, 1); cout << endl;
    baza2(6, 1); cout << endl;
    baza2(7, 1); cout << endl;
    //baza2(15); cout << endl;
    return 0;
}
