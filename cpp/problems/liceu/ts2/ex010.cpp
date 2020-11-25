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

void binar() {
    int a = 257;
    /*while(a) {
        int r = a % 2;
        cout << r;
        a /= 2;
    }*/
    rec (a);
    cout << "\n"; 
}

void utilizare_masca() {
    int a = 257, i, j;
    char *adr_byte = (char*) &a, masca;
    for (i = 0; i < sizeof(a); i++) {
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

void utilizare_masca2() {
    int a = 257, i, j;
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
    double start = clock();
    binar();
    cout << "ran for " << (clock() - start) / CLOCKS_PER_SEC << " secs \n";
    start = clock();
    utilizare_masca2();
    cout << "ran for " << (clock() - start) / CLOCKS_PER_SEC << " secs \n";
    return 0;
}
