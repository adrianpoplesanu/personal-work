// TS1 e2 p166
#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
    int n, inv = 0;
    cout << "n = "; cin >> n;
    while (n) {
        inv *= 10;
        inv += n % 10;
        n /= 10;
    }
    cout << "inv = " << inv << endl;
    return 0;
}
