// TS1 e39 p115 pdf
#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
    int x, y, sx = 0, sy = 0;
    cout << "y = "; cin >> y;
    while (1) {
        x = 9 * y + 11 - 64 * ((int)((9 * y + 11) / 64));
        sx += x;
        if (sx >= 1000) {
            cout << "Man o' War" << endl;
            break;
        }
        y = 9 * x + 12 - 64 * ((int)((9 * x + 12) / 64));
        sy += y;
        if (sy >= 1000) {
            cout << "Swaps" << endl;
            break;
        }
    }
    return 0;
}
