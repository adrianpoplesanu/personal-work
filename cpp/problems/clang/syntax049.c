#include <stdio.h>

// COMPILE:	gcc syntax049.c
// USAGE:	./a.out
// BOOKMARK:	pg 49
// DESCRIPTION:	formatted printing of a bunch of numbers

void print_first_numbers(int n) {
    for (int i = 0; i < n; i++) {
        printf("%6d%c", i, (i%10==9 || i==n-1) ? '\n' : ' ');
    }
}

int main(int argc, char *argv[]) {
    print_first_numbers(99);
    return 0;
}
