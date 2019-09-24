// TS1 e1 p166
#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
    int n, s = 0;
    cout << "n = "; cin >> n;
    while(n) {
        s += n % 10;
        n /= 10;
    }
    cout << "s = " << s << endl;
    return 0;
}
