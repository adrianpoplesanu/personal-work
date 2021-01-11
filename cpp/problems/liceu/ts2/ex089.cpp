// ts2 p47 e11 ver b
#include <iostream>
using namespace std;

int coeficient(int n, int k) {
    int sus = 1, jos = 1;
    for (int i = 1; i <= n; i++) sus *= i;
    for (int i = 1; i <= n - k; i++) jos *= i;
    for (int i = 1; i <= k; i++) jos *= i;
    return sus / jos;
}

int main(int argc, char *argv[]) {
    int n;
    cout << "n = "; cin >> n;
    for (int i = 0; i <= n; i++) cout << coeficient(n, i) << " ";
    cout << "\n";
    return 0;
}
