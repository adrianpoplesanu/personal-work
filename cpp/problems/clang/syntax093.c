// COMPILE:	gcc syntax092.c
// USAGE:	echo 11 22 33 aaa 5 0 3 -34 | ./a.out
// BOOKMARK:	pg 87
// DESCRIPTION:	ex 5-1, don't default non digit characters to zero in the array 

#include <stdio.h>

#define SIZE	128

int main(int argc, char *argv[]) {
    int n, array[SIZE], getint(int*, int*);
    int decrement = 0;
    for (n = 0; n < SIZE && getint(&array[n], &decrement) != EOF; n++) if (decrement) n--;

    for (int i = 0; i < n; i++) {
        printf("[ %3d ] %d\n", i, array[i]);
    }
    return 0;
}

#include <ctype.h>

#define BUFSIZE 100

char buf[BUFSIZE];
int bufp = 0;

int getch(void) {
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) {
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}

int getint(int *pn, int *decrement) {
    int c, sign;
    *decrement = 0;
    while (isspace(c = getch())) ;
    if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
        *decrement = 1;
        return 0;
    }
    sign = (c == '-') ? -1 : 1;
    if (c == '+' || c == '-') c = getch();
    if (!isdigit(c)) {
        *decrement = 1;
        return c;
    }
    for (*pn = 0; isdigit(c); c = getch()) *pn = 10 * *pn + (c - '0');
    *pn *= sign;
    if (c != EOF) ungetch(c);
    return c;
}
