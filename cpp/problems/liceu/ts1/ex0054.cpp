// TS1 e8 p110 pdf
#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
    int n, suma = 0, count = 0;
    do {
        cout << "n = "; cin >> n;
        suma += n;
        count++;
    } while(n != 0);
    if (count - 1) {
        cout << float(suma) / (count - 1) << endl;
    } else {
        cout << "niciun numar; div 0 error" << endl;
    }
    return 0;
}
