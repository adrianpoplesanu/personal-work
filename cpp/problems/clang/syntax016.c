#include <stdio.h>

#define IN	1
#define OUT	0

// USAGE: cat syntax016.c | ./a.out
// pg 23 ex 1.12

main() {
    int c, start, end, state;
    while((c = getchar()) != EOF) {
        if (c == ' ' || c == '\t' || c == '\n') {
            if (state == IN) {
                state = OUT;
                putchar('\n');
            }
        } else {
            state = IN;
            putchar(c);
        }
    }
}
