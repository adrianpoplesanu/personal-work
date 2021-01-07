// ts2 p46 e4
#include <iostream>
using namespace std;

float diagonala(int n) {
    return n * 1.42; // 1.42 aproximation for sqrt(2);
}

int main(int argc, char *argv[]) {
    int n;
    cout << "n = "; cin >> n;
    cout << diagonala(n) << "\n";
    return 0;
}
