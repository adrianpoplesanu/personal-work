#include <Foundation/Foundation.h>

int main(int argc, char *argv[]) {
    int (^power)(int, int) = ^(int base, int pew) {
        int result = 1;
        while(pew--) result *= base;
        return result;
    };
    int a = power(3, 3);
    printf("%i\n", a);
    a = power(2, 3);
    printf("%i\n", a);
    a = power(5, 3);
    printf("%i\n", a);
    return 0;
}
