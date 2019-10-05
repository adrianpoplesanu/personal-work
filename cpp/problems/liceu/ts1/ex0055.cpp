// TS1 e9 p110 pdf
#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
    int n, suma = 0, produs = 1, count = 0;
    do {
        cout << "n = "; cin >> n;
        count++;
        if(count % 2) suma += n;
        else if(n) produs *= n;
    } while (n != 0);
    cout << "s = " << suma << endl << "p = " << produs << endl;
    return 0;
}
