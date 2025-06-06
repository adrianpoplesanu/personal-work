#include <stdio.h>

// COMPILE:	gcc syntax066.c
// USAGE:	./a.out
// BOOKMARK:	pg 61
// DESCRIPTION:	found common elements without using goto

void common(int n, int a[], int m, int b[]) {
    int found = 0;
    for (int i = 0; i < n && !found; i++) {
        for (int j = 0; j < m && !found; j++) {
            if (a[i] == b[j]) found = 1;
        }
    }

    if (found) {
        printf("[ out ] there was a common element\n");
    } else {
        printf("[ out ] did not found common elements\n");
    }
}

int main(int argc, char *argv[]) {
    int a[] = {1, 2, 3, 4, 5};
    int b[] = {5, 6, 7, 8, 9};

    common(5, a, 5, b);

    return 0;
}
