// determinarea primelor n numere prime folosing un ciur
// programul afiseaza al 100000-lea numar prim
#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
    int v[1500000];
    for (int i = 0; i < 1500000; ++i) v[i] = 0;
    v[0] = 1;
    v[1] = 1;
    for (int i = 2; i < 1500000; ++i) {
        if (v[i] == 1) continue;
        else {
            for (int j = 2 * i; j < 1500000; j += i) { // 2-ul asta inseamna de la al doilea multilpu
                v[j] = 1;                              // al numarului prim, catre urmatorii multipli
            }
        }
    }
    int m = 0;
    int i = 0;
    while (m < 100000) {
        if (v[i] == 0) m++;
        ++i;
    }
    cout << i - 1 << "\n";
    return 0;
}
