// ts2 p46 e6
#include <iostream>
using namespace std;

bool verifica_triunghi(int a, int b, int c) {
    return (a < b + c) && (b < a + c) && (c < a + b);
}

int main(int argc, char *argv[]) {
    int a, b, c;
    cout << "a = "; cin >> a;
    cout << "b = "; cin >> b;
    cout << "c = "; cin >> c;
    cout << verifica_triunghi(a, b, c) << "\n";
    return 0;
}
