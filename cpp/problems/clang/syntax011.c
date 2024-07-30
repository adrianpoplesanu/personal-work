#include <stdio.h>

// USAGE cat syntax001.c | ./a.out
// USAGE echo "aaa" | ./a.out

/* count characters in inputl 2nd version */
main() {
    double nc;

    for (nc = 0; getchar() != EOF; ++nc);
    printf("%.0f\n", nc);
}
