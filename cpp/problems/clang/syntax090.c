// COMPILE:	gcc syntax090.c
// USAGE:	./a.out
// BOOKMARK:	pg 85
// DESCRIPTION:	swap with pointers

#include <stdio.h>

void swap(int *px, int *py) {
    int temp = *px;
    *px = *py;
    *py = temp;
}

int main(int argc, char *argv[]) {
    int a = 5, b = 7;
    swap(&a, &b);
    printf("[ LOG ] a = %d ; b = %d\n", a, b);
    return 0;
}
