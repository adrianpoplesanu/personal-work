#include <iostream>
using namespace std;

void func(int p, ...) { // iti trebuie minim un argument pozitional, altfel nu vrea
    va_list args;
    va_start(args, p);
    cout << "buna dimineata!\n";
    if (p == 1) {
        int s = va_arg(args, int);
        cout << s << "\n";
    }
    va_end(args);
}

int main(int argc, char *argv[]) {
    void(*p)(int, ...);
    p = func;
    func(0);
    p(0);
    void *ptr = (void*)p;
    ((void(*)(...))ptr)(0);
    ((void(*)(...))ptr)(1, 5);

    return 0;
}