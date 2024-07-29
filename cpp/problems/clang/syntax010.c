#include <stdio.h>

// USAGE: cat syntax001.c | ./a.out 

main() {
    long nc;
    nc = 0;
    while (getchar() != EOF) ++nc;
    printf("%ld\n", nc);
}
