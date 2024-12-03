#include <stdio.h>

// COMPILE:	gcc syntax066.c
// USAGE:	./a.out
// BOOKMARK:	pg 61
// DESCRIPTION:	found common elements using goto

int main(int argc, char *argv[]) {
    int a[] = {1, 2, 3, 4, 5};
    int b[] = {5, 6, 7, 8, 9};

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (a[i] == b[j]) goto found;
        }
    }

    found:
        printf("there was a common element\n");
    return 0;
}
