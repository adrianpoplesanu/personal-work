#include <stdio.h>

// COMPILE:	gcc syntax066.c
// USAGE:	./a.out
// BOOKMARK:	pg 61
// DESCRIPTION:	found common elements using goto

void common(int n, int a[], int m, int b[]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (a[i] == b[j]) goto found;
        }
    }
    printf("[ out ] did not found common elements\n");
    return;

    found:
        printf("[ out ] there was a common element\n");
}

int main(int argc, char *argv[]) {
    int a[] = {1, 2, 3, 4, 5};
    int b[] = {6, 7, 8, 9};

    common(5, a, 4, b);

    return 0;
}
