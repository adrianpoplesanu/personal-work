// TS2 p8 e1
#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
    int a = 3, *adr = &a;
    ++*adr;
    cout << *adr << "\n";
    return 0;
}
