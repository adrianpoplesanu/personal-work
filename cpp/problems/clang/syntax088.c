// COMPILE:	gcc syntax088.c
// USAGE:	./a.out
// BOOKMARK:	pg 81 ex 4-14
// DESCRIPTION:	swap as a macro

#include <stdio.h>

#define SWAP(t, x, y) { t aux = x; x = y; y = aux; }

int main(int argc, char *argv[]) {
    int a = 5, b = 7;
    SWAP(int, a, b);
    printf("[ a ] %d\n", a);
    printf("[ b ] %d\n", b);

    float c = 1.2, d = 2.3;
    SWAP(float, c, d);
    printf("[ c ] %f\n", c);
    printf("[ d ] %f\n", d);
    return 0;
}
