#include <stdio.h>

// COMPILE:	gcc syntax060.c
// USAGE:	./a.out
// BOOKMARK:	pg 59
// DESCRIPTION:	itoa with padding

void reverse(char s[], int n) {
    int i, j, c;
    for (i = 0, j = n - 1; i < j; i++, j--)
        c = s[i], s[i] = s[j], s[j] = c;
}

void itoa(int n, char s[], int p) {
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
    while(i < p) {
        s[i++] = ' ';
    }
    s[i] = '\0';
    reverse(s, i);
}

int main(int argc, char *argv[]) {
    int n = 123;
    char s[10];
    itoa(n, s, 6);
    printf("%s\n", s);
    return 0;
}
