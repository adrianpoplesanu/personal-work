#include <iostream>
#include <fstream>
#include "big_number.h"
#include "big_number.cpp"
using namespace std;

int main(int argc, char *argv[]) {
    running();
    BigNumber numar1, numar2, numar3;
    numar1.LoadFromString("44748564589467812374783957123");
    numar2.LoadFromString("10000000000000000000000000000");
    numar3 = numar1 + numar2;
    numar3.PrintNumber();
    numar1.Add(numar2);
    numar1.PrintNumber();
    return 0;
}
