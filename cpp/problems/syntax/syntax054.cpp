#include <iostream>
using namespace std;

void baza2(int n, int val) {
    int c = n % 2;
    if (n > 0) {
        if (c) cout << val << " ";
        baza2(n/2, val + 1);
    }
}

int main(int argc, char *argv[]) {
    int n, a = 1;
    cout << "n = "; cin >> n;
    a = a << n;
    //for (int i = 1 << (n-1); i <= 1 << n; i++) {
    for (int i = 1; i < 1 << n; i++) {
        //cout << i << endl;
        baza2(i, 1); cout << endl;
    }
    return 0;
}
