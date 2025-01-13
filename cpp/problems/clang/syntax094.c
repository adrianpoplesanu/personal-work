// COMPILE:	gcc syntax094.c
// USAGE:	echo 11.22 33.156 | ./a.out
// BOOKMARK:	pg 87 ex 5-2
// DESCRIPTION:	scanf floats to arrays

#include <stdio.h>

#define SIZE	128

int main(int argc, char *argv[]) {
    int n, getint(int*), getfloat(float*);
    float array[SIZE];
    for (n = 0; n < SIZE && getfloat(&array[n]) != EOF; n++);

    for (int i = 0; i < n; i++) {
        printf("[ %3d ] %f\n", i, array[i]);
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
        return 0;
    }
    sign = (c == '-') ? -1 : 1;
    if (c == '+' || c == '-') c = getch();
    for (*pn = 0; isdigit(c); c = getch()) *pn = 10 * *pn + (c - '0');
    *pn *= sign;
    if (c != EOF) ungetch(c);
    return c;
}

int getfloat(float *pn) {
    int c, sign;
    while (isspace(c = getch())) ;
    if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
        return 0;
    }
    sign = (c == '-') ? -1 : 1;
    if (c == '+' || c == '-') c = getch();
    for (*pn = 0; isdigit(c); c = getch()) *pn = 10 * *pn + (c - '0');
    *pn *= sign;
    if (c == '.') c = getch();
    float factor = 0.1;
    while (isdigit(c)) {
        *pn += (c - '0') * factor;
        factor /= 10;
        c = getch();
    }
    if (c != EOF) ungetch(c);
    return c;
}
