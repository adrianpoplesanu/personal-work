#include <iostream>
#include "big_number.h"
#include "big_number.cpp"
using namespace std;

int main(int argc, char *argv[]) {
    cout << "running minus test..." << endl;
    BigNumber numar1, numar2, numar3;
    numar1.LoadFromString("6");
    numar2.LoadFromString("5");
    numar3 = numar1 - numar2;
    numar3.PrintLineNumber();
    return 0;
}