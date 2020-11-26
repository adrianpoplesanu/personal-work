// ts2 p10 e1
#include <iostream>
#include <time.h>
using namespace std;

void rec(int n) {
    if (n != 0) {
        rec(n / 2);
        cout << n % 2;
    }
}

void binar(int a) {
    rec (a);
    cout << "\n"; 
}

void utilizare_masca(int a) {
    int i, j;
    char *adr_byte = (char*) &a, masca;
    for (i = 0; i < sizeof(a) / 2; ++i) {
        masca = 128;
        for (j = 0; j < 8; j++) {
            if (*adr_byte & masca) cout << 1;
            else cout << 0;
            masca >>= 1;
        }
        adr_byte++;
    }
    cout << "\n";
}

int main(int argc, char *argv[]) {
    double start = clock(), method1, method2;
    for (int i = 257; i < 259; ++i) binar(i);
    method1 = clock() - start;
    start = clock();
    for (int i = 257; i < 259; ++i) utilizare_masca(i);
    method2 = clock() - start;

    cout << "regular div method ran for " << method1 / CLOCKS_PER_SEC << " secs \n";
    cout << "mask method ran for " << method2 / CLOCKS_PER_SEC << " secs \n";
    return 0;
}
