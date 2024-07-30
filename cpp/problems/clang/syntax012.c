#include <stdio.h>

// USAGE: cat syntax012.c | ./a.out

main() {
    int c, nl;

    nl = 0;
    while((c = getchar()) != EOF) {
        if (c == '\n') ++nl;
    }
    printf("%d\n", nl);
}
