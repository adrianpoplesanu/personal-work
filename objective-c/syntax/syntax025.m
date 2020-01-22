#include <Foundation/Foundation.h>

int main(int argc, char *argv[]) {
    int (^power)(int, int) = ^(int base, int pew) {
        return base * pew;
    };
    int a = power(3, 2);
    printf("%i\n", a);
    return 0;
}
