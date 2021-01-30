#include <iostream>
using namespace std;

int tot = 0;

void calculate(int a[10], int n, int s) {
    if (s == 0) {cout << "solution!"; tot++;}
    else if (s > 0) {
        for (int i = 0; i < n; ++i) calculate(a, n, s - a[i]);
    }
}

int main(int argc, char *argv[]) {
    int a[10] = {2, 3, 10, 11}, n = 3, s = 23;
    calculate(a, n, s);
    cout << "\n" << tot << "\n";
    return 0;
}
