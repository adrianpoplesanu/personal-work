#include <iostream>
#include <vector>
#include "objects.h"
#include "objects.cpp"
#include "listobject.h"
#include "listobject.cpp"


void memory_test() {
    PyObjectList lo;
    lo.append(new PyObjectString("ana"));
    lo.append(new PyObjectString("are"));
    lo.append(new PyObjectInt(2));
    lo.append(new PyObjectString("mere"));
    std::cout << lo.str() << '\n';
    std::cout << &lo << '\n';
    //lo.repr();
    std::cout << lo.repr() << '\n';
}

int main(int argc, char *argv[]) {
    memory_test();
    memory_test();
    return 0;
}