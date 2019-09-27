// TS1 e3 p103 pdf
#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
    int n, s = 0;
    cout << "n = "; cin >> n;
    for (int i = 1; i <= n; i++) {
        s += i;
    }
    cout <<"s = " << s << endl;
    return 0;
}
