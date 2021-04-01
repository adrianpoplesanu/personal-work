#include <iostream>
#include "test.h"
#include "test.cpp"
using namespace std;

int main(int argc, char *argv[]) {
    cout << "Monkey interpreter in C++ 0.1\n";
    Test test33(33);
    test33.RunAllTests();
    //test33.RunTokenTypeTest(); //... passed
    //Test test34(34);
    //test34.RunLexerTest(); //... passed
    //Test test45(45);
    //test45.RunToStringTest(); //... passed
    return 0;
}
