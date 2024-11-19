#include <stdio.h>

// COMPILE:	gcc syntax059.c
// USAGE:	./a.out
// BOOKMARK:	pg 58
// DESCRIPTION:	reverse, but fewer lines of code

void reverse(char s[], int n) {
    int i, j, c;
    for (i = 0, j = n - 1; i < j; i++, j--)
        c = s[i], s[i] = s[j], s[j] = c;
}

int main(int argc, char *argv[]) {
    char text[] = "buna dimineata!";
    reverse(text, 15);
    printf("[ OUT ] %s\n", text);
    return 0;
}
