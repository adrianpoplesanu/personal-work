// TS1 e15 p132
#include <iostream>
using namespace std;

char transform(int k) {
    if (k == 0) return 'a';
    if (k == 1) return 'b';
    if (k == 2) return 'c';
    if (k == 3) return 'd';
    if (k == 4) return 'e';
    if (k == 5) return 'f';
    if (k == 6) return 'g';
    if (k == 7) return 'h';
    if (k == 8) return 'i';
    if (k == 9) return 'j';
    return '-';
}

void convert(int n) {
    if (n > 9) {
        int r = n % 10;
        convert(n/10);
        cout << transform(r);
    } else {
        cout << transform(n);
    }
}

int main (int argc, char *argv[]) {
    int n;
    cout << "n = "; cin >> n;
    convert(n);
    cout << endl;
    return 0;
}
