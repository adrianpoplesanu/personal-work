#include <iostream>

class B;

class A {
public:
    B *b;
    A() {

    }
    A(B *b2) {
        b = b2; 
    }
    void check() {
        std::cout << "aaa\n";
    }
};

class B {
public:
    A a;
    void check() {
        std::cout << "bbb\n";
    }
};

int main(int argc, char *argv[]) {
    B b;
    A a(&b);
    a.b->check();
    return 0;
}
