// COMPILE:	gcc syntax091.c
// USAGE:	echo 11 22 33 5 3 -34 | ./a.outt
// BOOKMARK:	pg 86
// DESCRIPTION:	scanf ints to array, damn son, this is some crazy sh!t

#include <stdio.h>

#define SIZE	128

int main(int argc, char *argv[]) {
    int n, array[SIZE], getint(int*);
    for (n = 0; n < SIZE && getint(&array[n]) != EOF; n++);

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

int getint(int *pn) {
    int c, sign;
    while (isspace(c = getch())) ;
    if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
        ungetch(c);
        return 0;
    }
    sign = (c == '-') ? -1 : 1;
    if (c == '+' || c == '-') c = getch();
    for (*pn = 0; isdigit(c); c = getch()) *pn = 10 * *pn + (c - '0');
    *pn *= sign;
    if (c != EOF) ungetch(c);
    return c;
}
