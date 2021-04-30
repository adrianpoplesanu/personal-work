#include <iostream>
#include "test.h"
#include "test.cpp"
#include "program.h"
#include "program.cpp"


int main(int argc, char *argv[]) {
    std::cout << "Monkey interpreter in C++ 0.1\n";
    //Test test33(33);
    //test33.RunAllTests();
    //test33.RunTokenTypeTest(); //... passed
    //Test test34(34);
    //test34.RunLexerTest(); //... passed
    //Test test45(45);
    //test45.RunToStringTest(); //... passed

    //Test test46(46);
    //test46.RunToStringSimpleTest();

    Test test47(47);
    test47.RunParserBuildStatementsTest();

    Test test48(48);
    test48.RunObjectReferenceTest();

    Program program;
    program.Loop();
    return 0;
}
