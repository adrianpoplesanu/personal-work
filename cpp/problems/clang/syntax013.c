#include <stdio.h>

// page 22 exercise
// USAGE: cat syntax013.c | ./a.out

main() {
    int c, total;
    total = 0;
    while ((c = getchar()) != EOF)
        if (c == ' ' || c == '\t' || c == '\n') ++total;
    printf("%d\n", total);
}
