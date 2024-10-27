#include <stdio.h>

// COMPILE:	gcc syntax046.c
// USAGE:	./a.out
// BOOKMARK:	none
// DESCRIPTION: print an unsinged int in binary

void print_digit(int a) {
    if (a == 0) return;
    print_digit(a / 2);
    if (a % 2 == 0) printf("0");
    else printf("1");
}

void print_binary(int a) {
    print_digit(a);
    printf("\n");
}

int main(int argc, char *argv[]) {
    print_binary(7);
    print_binary(8);
    return 0;
}
