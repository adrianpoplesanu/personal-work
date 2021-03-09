#ifndef __TEST_H
#define __TEST_H

class Test {
public:
    Test();
    Test(int);
    ~Test();
    int GetTestID();
    void RunTokenTypeTest();

private:
    int id;
};

#endif