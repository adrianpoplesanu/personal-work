#include <iostream>

// asta e in combinarie cu syntax255.cpp
// run command:
// $ leaks --atExit -- ./syntax259

void change (int *&a) {
    delete a; // asta a fost necesar pentru ca am la parametru *&a, in syntax 255 am doar *a si nu trebuie sa fac delete aici
    int *b = new int();
    a = new int();
    *a = 7;
    delete b;
}

int main(int argc, char *argv[]) {

    int *a = new int();
    *a = 5;

    std::cout << a << " " << *a << "\n";
    change(a);
    std::cout << a << " " << *a << "\n";

    delete a;

    return 0;
}
