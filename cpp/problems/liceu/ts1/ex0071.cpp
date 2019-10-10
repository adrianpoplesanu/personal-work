// TS1 e19 p111 pdf
#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
    int n = 0, c = 0;
    do {
        n = n * 10 + c;
        cout << "c = "; cin >> c;
    } while (c >= 0 and c < 10);
    cout << "n = " << n << endl;
    return 0;
}
