#include <stdio.h>

// COMPILE:	gcc syntax047.c
// USAGE:	./a.out
// BOOKMARK:	pg 47 ex 2-7
// DESCRIPTION: invert bits

void print_digit(int a) {
    if (a == 0) return;
    print_digit(a / 2);
    if (a % 2 == 0) printf("0");
    else printf("1");
}

void print_binary(int a) {
    print_digit(a);
    printf("\n");
}

unsigned invert(unsigned x, int p, int n) {
    int mask = (~(~0u << n)) << (p - n + 1);
    return mask ^ x;
}

int main(int argc, char *argv[]) {
    unsigned a = 100170;
    print_binary(a);
    unsigned b = invert(a, 6, 7);
    print_binary(b);
    return 0;
}
