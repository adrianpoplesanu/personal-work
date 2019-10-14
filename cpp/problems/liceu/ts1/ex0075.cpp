// TS1 e23 p112 pdf
#include <iostream>
#include <time.h>
using namespace std;

int main(int argc, char *argv[]) {
    int n, m;
    cout << "n = "; cin >> n;
    cout << "m = "; cin >> m;
    srand (time(NULL));
    for (int i = 0; i < 10; i++) {
        cout << n + rand() % (m - n + 1) << endl;
    }
    return 0;
}
