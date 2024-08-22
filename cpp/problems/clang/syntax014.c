#include <stdio.h>

// USAGE: cat syntax014.c | ./a.out
// exercise 1-9 pg 22

main() {
    int c;
    int blank = 0;
    while((c = getchar()) != EOF) {
        if (c == ' ' && blank) {
        
        } else if (c == ' ') {
            blank = 1;
            putchar(c);
        } else {
            blank = 0;
            putchar(c);
        }
    }
}
