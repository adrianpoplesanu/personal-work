#include <stdio.h>

// COMPILE:	gcc syntax032.c
// USAGE:	./a.out
// BOOKMARK:	pg 38
// DESCRIPTION:	enum examples

enum boolean {
    YES, NO
};

enum escapes {
    BELL = '\a',
    BACKSPACE = '\b',
    TAB = '\t',
    NEWLINE = '\n',
    VTAB = '\v',
    RETURN = '\r'
};

enum months {
    JAN = 1, FEB, MAR, APR, MAY, JUN, JUL, AUG, SEP, OCT, NOV, DEC
};

int main() {
    printf("this runs\n");
    return 0;
}
