// TS1 e13 p110 pdf v2 - reading with cin.get
#include <iostream>
using namespace std;

int cifra(char c) {
    if (c == '0') return 0;
    if (c == '1') return 1;
    if (c == '2') return 2;
    if (c == '3') return 3;
    if (c == '4') return 4;
    if (c == '5') return 5;
    if (c == '6') return 6;
    if (c == '7') return 7;
    if (c == '8') return 8;
    if (c == '9') return 9;
    if (c == 'a') return 10;
    if (c == 'b') return 11;
    if (c == 'c') return 12;
    if (c == 'd') return 13;
    if (c == 'e') return 14;
    if (c == 'f') return 15;
    return 0;
}

int main(int argc, char *argv[]) {
    int n = 0;
    char c;
    cout << "c = ";
    do {
        cin.get(c);
        if (c == '\n') break;
        if (n == 0 && c == '0') { cout << "must not start with 0"; return 1; }
        n *= 16;
        n += cifra(c);
    } while(1);
    cout << n << endl;
    return 0;
}
