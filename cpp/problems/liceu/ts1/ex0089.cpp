// TS1 e36 p114 pdf v1
#include <iostream>
using namespace std;

bool is_good(int number) {
    int a[10];
    for (int i = 0; i < 10; i++) a[i] = 0;
    while(number) {
        int c = number % 10;
        number /= 10;
        if (c % 2 == 0 || a[c] == 1) return false;
        a[c] = 1;
    }
    return true;
}

int main(int argc, char *argv[]) {
    int s = 0;
    for (int i = 0; i < 100000; i++) {
        if (is_good(i)) {
            s += i;
            cout << i << endl;
        }
    }
    cout << "s = " << s << endl;
    return 0;
}
