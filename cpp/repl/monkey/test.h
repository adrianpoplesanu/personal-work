#ifndef __TEST_H
#define __TEST_H

class Test {
public:
    Test();
    Test(int);
    ~Test();
    int GetTestID();
    void RunAllTests();
    void RunTokenTypeTest();
    void RunLexerTest();
    void RunToStringTest();
    void RunToStringSimpleTest();
    void RunParserBuildStatementsTest();
    void RunObjectReferenceTest();

private:
    int id;
};

#endif