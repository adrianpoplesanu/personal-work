// TS1 e13 pg132
#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
    int n, c, nr = 0;
    cout << "n = "; cin >> n;
    while (n--) {
        cout << "c = "; cin >> c;
        if (c < 0 || c > 9) {
            cout << "cifra invalida" << endl;
            n++;
            continue;
        }
        nr *= 10;
        nr += c;
    }
    cout << "nr = " << nr << endl;
    return 0;
}
