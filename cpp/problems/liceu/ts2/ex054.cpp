// ts2 p30 e2
#include<iostream>
using namespace std;

int suma (int a, int b) {
    return a + b;
}

int main(int argc, char *argv[]) {
    int c = 4, d = 3;
    cout << suma (2, 3) << '\n';
    cout << suma (2 + 7, 3 - 1 * 2) << '\n';
    cout << suma (c, d) << '\n';
    cout << suma (1.9, 3.3) << '\n';
    return 0;
}
