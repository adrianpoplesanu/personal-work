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

int main(int argc, char *argv[]) {
    cout << "disassemble me!" << endl;
    return 0;
}
