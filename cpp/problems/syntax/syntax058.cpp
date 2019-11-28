#include <iostream>
#define FOR(i, a, b) for(int i = a; i < b; i++)
using namespace std;

int main(int argc, char *argv[]) {
    FOR(i, 0, 10) cout << i << endl;
    int suma = 0;
    FOR(i, 0, 10) {
        suma += i;
    }
    cout << suma << endl;
    return 0;
}
