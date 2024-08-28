#include <stdio.h>

// COMPILATION: gcc syntax018.c
// USAGE: cat syntax018.c | ./a.out
// BOOKMARK: pg 25 ex 1-13

#define IN	1
#define OUT	0

main() {
    int c, i, state, current_len = 0, size[40];

    for (i = 0; i < 40; ++i) size[i] = 0;

    while ((c = getchar()) != EOF) {
        if (c == ' ' || c == '\t' || c == '\n') {
            if (state == IN) {
                state = OUT;
                ++size[current_len];
                current_len = 0;
            }
        } else {
            state = IN;
            ++current_len;
        }    
    }

    for (i = 0; i < 40; ++i) printf("%d: %d\n", i, size[i]);
}
