#include <stdio.h>

// COMPILE: gcc syntax20.c
// USAGE: ./a.out

int power(int m, int n);

int main() {
    int i;
    for (i = 0; i < 10; ++i) printf("%d %d %d\n", i, power(2, i), power(-3, i));
    return 0;
}

int power(int base, int n) {
    int i, p;
    p = 1;
    for (i = 0; i < n; ++i) p = p * base; // cam scolaresti aici domnii Kernighan si Ritchie
    return p;
}
