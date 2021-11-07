#include <iostream>

int main(int argc, char *argv[]) {
    char a[10] = {'a', 'd', 'i', 's', 'h'};
    char *p;

    p = a;
    while(*p) {
        std::cout << *p;
        p++;
    }

    std::cout << '\n';
    return 0;
}
