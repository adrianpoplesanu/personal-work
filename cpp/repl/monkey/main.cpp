#include <iostream>
#include "test.h"
#include "test.cpp"
using namespace std;

int main(int argc, char *argv[]) {
    cout << "Monkey interpreter in C++ 0.1\n";
    Test test33(33);
    test33.RunTokenTypeTest();
    Test test34(34);
    test34.RunLexerTest();
    Test test45(45);
    test45.RunToStringTest();
    return 0;
}
