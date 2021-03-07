// ts2 p61 e1
#include <iostream>
using namespace std;

struct complex {
    int m, n;
};

int main(int argc, char *argv[]) {
    complex *adr;
    cout << adr << '\n';
    cout << &adr << '\n';
    adr = new complex;
    cout << adr << '\n';
    cout << &adr << '\n';
    adr->m = 7;
    adr->n = 5;
    cout << adr->m << " " << adr->n << '\n';
    delete adr;
    return 0;
}
