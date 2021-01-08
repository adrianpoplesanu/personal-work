// ts2 p46 e8
#include <iostream>
using namespace std;

int last_digit(int n) {
    return n % 10;
}

int main(int argc, char *argv[]) {
    int n;
    cout << "n = "; cin >> n;
    cout << last_digit(n) << "\n";
    return 0;
}
