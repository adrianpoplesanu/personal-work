// TS1 e2 p 168
#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
    int n, i = 2, f;
    cout << "n = "; cin >> n;
    do {
        f = 0;
        while (n % i == 0) {
            n /= i;
            f++;
        }
        if (f) cout << i << " la puterea " << f << endl;
        i++;
    } while (n > 1);
    return 0;
}
