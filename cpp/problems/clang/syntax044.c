#include <stdio.h>

// COMPILE:	gcc syntax044.c
// USAGE:	./a.out
// BOOKMARK:	pg 47 ex 2-6
// DESCRIPTION:	set bits from a different int

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

unsigned setbits(unsigned x, int p, int n, unsigned y);

int main(int argc, char *argv[]) {
    unsigned a = 170;
    unsigned b = 7;
    //print_binary(a);
    //print_binary(b);
    unsigned c = setbits(a, 4, 3, b);
    printf("%u\n", c);
    print_binary(c);
    return 0;
}

unsigned setbits(unsigned x, int p, int n, unsigned y) {
    // i really don't like this
    // Create a mask for the n bits at position p in x
    unsigned mask = ((1 << n) - 1) << (p + 1 - n);
    
    print_binary(mask);
    // Shift the rightmost n bits of y into the correct position
    unsigned y_bits = (y & ((1 << n) - 1)) << (p + 1 - n);
   
    print_binary(y_bits);
    // Clear the n bits at position p in x and set them to the bits from y
    return (x & ~mask) | y_bits;
}
