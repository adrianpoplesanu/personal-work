// COMPILE:	gcc syntax081.c
// USAGE:	./a.out
// BOOKMARK:	pg 78
// DESCRIPTION:	recursive itoa

#include<stdio.h>

void printd(int n) {
    if (n < 0) {
        putchar('-');
        n = -n;
    }
    if (n / 10) printd(n / 10);
    putchar(n % 10 + '0');
}

int main(int argc, char *argv[]) {
    printd(123);
    printf("\n");
    return 0;
}
