#include <stdio.h>

// COMPILE:	gcc syntax060.c
// USAGE:	./a.out
// BOOKMARK:	pg 59
// DESCRIPTION:	itoa

void reverse(char s[], int n) {
    int i, j, c;
    for (i = 0, j = n - 1; i < j; i++, j--)
        c = s[i], s[i] = s[j], s[j] = c;
}

void itoa(int n, char s[]) {
    int i, sign;

    if ((sign = n) < 0) {
        n = -n;
    }
    i = 0;
    do {
        s[i++] = n % 10 + '0';
    } while((n /= 10) > 0);
    if (sign < 0) {
        s[i++] = '-';
    }
    s[i] = '\0';
    reverse(s, i);
}

int main(int argc, char *argv[]) {
    int n = 123;
    char s[10];
    itoa(n, s);
    for (int i = 0; i < 3; i++) {
        printf("%c\n", s[i]);
    }
    return 0;
}
