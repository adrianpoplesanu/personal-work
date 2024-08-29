#include <stdio.h>

// COMPILATION: gcc syntax019.c
// USAGE: cat syntax019.c | ./a.out
// BOOKMARK: pg 25 ex 1-13b

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

    for (i = 0; i < 40; ++i) {
        printf("%.2d: ", i);
        for (int j = 0; j < size[i]; ++j) printf("=");
        printf("\n");
    }
}
