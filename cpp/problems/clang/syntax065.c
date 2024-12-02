#include <stdio.h>

// COMPILE:	gcc syntax065.c
// USAGE:	./a.out
// BOOKMARK:	pg 60
// DESCRIPTION:	skip negative elements in array

int main(int argc, char *argv[]) {
    int a[] = { 1, -4, 5, -8, 2, -3, 9};
    int n = 7;

    printf("[ out ]");
    for (int i = 0; i < n; i++) {
        if (a[i] < 0) {
            continue;
        }
        printf(" %i", a[i]);
    }
    printf("\n");
    return 0;
}
