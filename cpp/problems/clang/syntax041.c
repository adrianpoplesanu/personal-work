#include <stdio.h>

// COMPILE:	gcc syntax041.c
// USAGE:	./a.out
// BOOKMARK:	pg 47
// DESCRIPTION:	crazy bitwise operations

unsigned getbits(unsigned x, int p, int n) {
    return (x >> (p+1-n)) & ~(~0 << n);
}

int main(int argc, char *argv[]) {
    unsigned out;
    out = getbits(11, 4, 3);
    printf("[ RESULT ] %d\n", out);

    out = getbits(128, 4, 3);
    printf("[ RESULT ] %d\n", out);

    out = getbits(15, 4, 3);
    printf("[ RESULT ] %d\n", out);

    out = getbits(31, 4, 3);
    printf("[ RESULT ] %d\n", out);
    return 0;
}
