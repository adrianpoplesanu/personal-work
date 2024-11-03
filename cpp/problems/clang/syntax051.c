#include <stdio.h>

// COMPILE:	gcc syntax051.c
// USAGE:	./a.out
// BOOKMARK:	pg 54
// DESCRIPTION: binary search

int binsearch(int x, int v[], int n) {
    int low, high, mid;
    low = 0;
    high = n - 1;
    while (low <= high) {
        mid = (low + high) / 2;
        if (x < v[mid]) {
            high = mid - 1;
        } else if (x > v[mid]) {
            low = mid + 1;
        } else {
            return mid;
        }
    }
    return -1;
}

int main(int argc, char *argv[]) {
    int a[] = {1, 2, 3, 5, 6, 7, 9};
    printf("[ OUT ] %d\n", binsearch(4, a, 7));
    printf("[ OUT ] %d\n", binsearch(3, a, 7));
    printf("[ OUT ] %d\n", binsearch(1, a, 7));
    printf("[ OUT ] %d\n", binsearch(9, a, 7));
    return 0;
}
