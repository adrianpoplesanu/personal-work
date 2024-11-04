#include <stdio.h>

// COMPILE:	gcc syntax051.c
// USAGE:	./a.out
// BOOKMARK:	pg 54
// DESCRIPTION: binary search cu un singur if in loop, interensat, ar trebui sa testez performanta

int binsearch(int x, int v[], int n) {
    int low, high, mid;
    low = 0;
    high = n - 1;
    while (low < high - 1) {
        mid = (low + high) / 2;
        if (x < v[mid]) {
            high = mid - 1;
        } else {
            low = mid; 
        }
    }
    if (x == v[low]) return low;
    if (x == v[high]) return high;
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
