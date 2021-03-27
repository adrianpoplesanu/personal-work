#include <iostream>
#include <map>
using namespace std;

void foo(void) {
    int a = 5;
    cout << a * a << "\n";
}

void bar(int b) {
    cout << b * b << "\n";
}

int main(int argc, char *argv[]) {
    void (*p)(void);
    map<int, void*> m;
    p = foo;
    p();
    void (*p2)(int);
    p2 = bar;
    p2(3);
    void *test;
    // boxing a function pointer
    test = (void *)p;
    // unboxing a function pointer
    ((void (*)())test)();

    // boxing a function pointer
    test = (void *)p2;
    // unboxing a function pointer
    ((void (*)(int))test)(2);

    m.insert(pair<int, void *>(0, (void *)p));
    m.insert(pair<int, void *>(1, (void *)p2));

    ((void (*)(int))m.find(1)->second)(4);
    return 0;
}