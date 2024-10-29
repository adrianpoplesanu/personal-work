#include <stdio.h>

// COMPILE:	gcc syntax048.c
// USAGE:	./a.out
// BOOKMARK:	pg 48
// DESCRIPTION:	1-bit counter, ex: 110011 returns 4

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

int bitcount(unsigned int x) {
    int b;
    for (b = 0; x != 0; x >>= 1) {
        if (x & 01) b++;
    }
    return b;
}

int main(int argc, char *argv[]) {
    int res = bitcount(100000);
    print_binary(100000);
    printf("[ LOG ] %d\n", res);
    return 0;
}
