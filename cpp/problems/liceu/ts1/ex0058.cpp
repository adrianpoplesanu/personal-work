// TS1 e11 p110 pdf v2
#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
    int n;
    float e = 0;
    cout << "n = "; cin >> n;
    for (int i = 0; i++ < n; ) {
        e += float(i) / ((i + 1) * (i + 2));
    }
    cout << "e = " << e << endl;
    return 0;
}
