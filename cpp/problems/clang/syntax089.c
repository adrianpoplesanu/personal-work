// COMPILE:	gcc syntax089.c
// USAGE:	./a.out
// BOOKMARK:	pg 84
// DESCRIPTION:	a simple pointer example

#include <stdio.h>

int main(int argc, char *argv[]) {
    int x = 1, y = 2, z[10];
    int *ip;

    ip = &x;
    y = *ip;
    *ip = 0;
    ip = &z[0];

    return 0;
}
