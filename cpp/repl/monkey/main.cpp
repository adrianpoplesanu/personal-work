#include <iostream>
#include "test.h"
#include "test.cpp"
using namespace std;

int main(int argc, char *argv[]) {
    cout << "Monkey interpreter in C++ 0.1\n";
    Test test(33);
    test.RunTokenTypeTest();
    return 0;
}
