// TS1 e22 p111 pdf
#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
    float seed, n;
    cout << "seed = "; cin >> seed;
    cout << "iter = "; cin >> n;
    while(n--) {
       float trun = (float)(((int)(seed * 100000000) / 100) % 10000) * 0.0001;
       seed = trun * trun;
    }
    cout << seed << endl;
    return 0;
}
