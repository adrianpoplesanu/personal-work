// ts2 p47 e12
#include <iostream>
using namespace std;

bool prime_check(int n) {
    for (int i = 2; i < n; i++) if (n % i == 0) return false;
    return true;
}

int main(int argc, char *argv[]) {
    int n, m;
    cout << "n = "; cin >> n;
    cout << "m = "; cin >> m;
    for (int i = n; i <= m; i++) {
        if (prime_check(i)) cout << i << " ";
    }
    cout << "\n";
    return 0;
}
