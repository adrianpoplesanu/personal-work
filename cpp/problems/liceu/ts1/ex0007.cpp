// TS1 e7 p132
#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
    float S, p;
    int k;
    cout << "S = "; cin >> S;
    cout << "p% = "; cin >> p;
    cout << "k = "; cin >> k;
    while (k--) {
        S = S * (1 + p / 100);
    }
    cout << "S = " << S << endl;
    return 0;
}
