#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
    int n = 60, bin = 0, ordin = 1, r;
    while (n != 0) {
        r = n % 2;
        n /= 2;
        bin += ordin * r;
        ordin *= 10;
    }
    cout << bin << "\n";
    return 0;
}
