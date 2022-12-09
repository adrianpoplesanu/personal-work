#include <iostream>

int main(int argc, char* argv[]) {
    int* a = new int();
    *a = 5;
    delete a;
    a = NULL;
    if (a) {
        delete a;
    }
    return 0;
}
