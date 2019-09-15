// TS1 ex 2 pg 132
#include <iostream>

using namespace std;

int main(int argc, char* argv[]) {
    int n, produs = 1;
    cin >> n;
    while (n != 0) {
        int cifra = n % 10;
        produs *= cifra;
        n /= 10;
    }
    cout << produs << endl;
    return 0;
}
