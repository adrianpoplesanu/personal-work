// ts2 p41 e1
#include <iostream>
using namespace std;

bool test_number(int n) {
    int ones = 0, zeros = 0, r;
    while (n != 0) {
        r = n % 2;
        n /= 2;
        if (r == 0) zeros++;
        if (r == 1) ones++;
    }
    return zeros == ones;
}

int main(int argc, char *argv[]) {
    int n;
    cout << "n = "; cin >> n;
    for (int i = 1; i < n; ++i) {
        if (test_number(i)) cout << i << " ";
    }
    cout << "\n";
    return 0;
}
