#include <stdio.h>

// COMPILE:	gcc syntax045.c
// USAGE:	./a.out
// BOOKMARK:	none
// DESCRIPTION: playing aroung with bitwise operators

int main(int argc, char *argv[]) {
    unsigned int a = 170;
    unsigned int b = (a >> 2) & ~(~0u << 3);
    unsigned int c = ~(~0u << 3);
    unsigned int d = a & c;
    unsigned int e = 7 & c;
    unsigned int f = 8 & c;
    unsigned int g = ~0;
    printf("%u\n", a);
    printf("%u\n", b);
    printf("%u\n", c);
    printf("%u\n", d);
    printf("%u\n", e);
    printf("%u\n", f);
    printf("%u\n", g);
    return 0;
}
