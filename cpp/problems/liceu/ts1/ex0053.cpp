// TS1 e7 p110 pdf
#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
    int n, i, min;
    bool setat = false;
    cout << "n = "; cin >> n;
    while(n--) {
        cout << "i = "; cin >> i;
        if (!setat) {
            setat = true;
            min = i;
        } else {
            if (i < min) min = i;
        }
    }
    cout << "min = " << min << endl;
    return 0;
}
