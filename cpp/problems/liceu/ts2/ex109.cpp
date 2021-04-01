// ts2 p68 e1
// manna-pnueli
#include <iostream>
using namespace std;

int st[100], k, n;

int main(int argc, char *argv[]) {
    cout << "n = "; cin >> n;
    k = 1;
    st[k] = n;
    while (k > 0) {
        if (st[k] < 12) {
            k++;
            st[k] = st[k - 1] + 2;
        } else {
            k--;
            if (k > 0) st[k] = st[k + 1] - 1;
        }
    }
    cout << st[1] - 1 << "\n";
    return 0;
}