// in linux
// g++ syntax98.cpp -c -o syntax98.o
// nm syntax98.o

// in macos
// ca sa vezi codul de asembler generat
// otools -tv nume_fisier
// in linux
// objdump -d nume_fisier


#include <iostream>
using namespace std;

void swap(int &a, int &b) {
    int c = a;
    a = b;
    b = c;
}

int main(int argc, char *argv[]) {
    int a = 3, b = 5;
    swap(a, b);
    cout << a << b << endl;
    return 0;
}
