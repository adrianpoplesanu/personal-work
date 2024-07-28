#include <stdio.h>
// ctrl + d

// USAGE: cat syntax001.c | ./a.out
// USAGE: echo "aaa" | ./a.out

main() {
    int c;
    c = getchar();
    while (c != EOF) {
        putchar(c);
        c = getchar();
    }
}
