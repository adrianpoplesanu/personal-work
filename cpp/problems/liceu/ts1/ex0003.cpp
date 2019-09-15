#include <iostream>
using namespace std;

void max(int c1, int c2, int c3) {
    if (c1 >= c2 && c1 >= c3) {
        cout << c1;
        if (c2 >= c3) cout << c2 << c3;
        else cout << c3 << c2;
    } else
    if (c2 >= c1 && c2 >= c3) {
        cout << c2;
        if (c1 >= c3) cout << c1 << c3;
        else cout << c3 << c1;
    } else
    if (c3 >= c1 && c3 >= c2) {
        cout << c3;
        if (c1 >= c2) cout << c1 << c2;
        else cout << c2 << c1;
    }
    cout << endl;
}

int main(int argc, char* argv[]) {
    int n;
    cout << "n = "; cin >> n;
    int c1 = n % 10;
    n /= 10;
    int c2 = n % 10;
    n /= 10;
    int c3 = n % 10;
    max(c1, c2, c3);
    return 0;
}
