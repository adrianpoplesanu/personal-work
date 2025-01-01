// COMPILE:	gcc syntax085.c
// USAGE:	./.a.out
// BOOKMARK:	pg 79 ex 4-12
// DESCRIPTION:	recursive itoa

#include <stdio.h>

void my_itoa(char s[], int n) {
    static int i = 0;

    if (n != 0) {
        if (n < 0) {
            s[i++] = '-';
            n = -n;
            s[i] = '\0';
            my_itoa(s, n);
        } else {
            char temp = n % 10 + '0';
            my_itoa(s, n / 10);
            s[i++] = temp;
            s[i] = '\0';
        }
    }
}

int main(int argc, char *argv[]) {
    char s[100];
    my_itoa(s, -123);
    printf("%s\n", s);
    return 0;
}
