#include <stdio.h>
#include <string.h>

// COMPILE:	gcc sumtax058.c
// USAGE:	./a.out
// BOOKMARK:	pg. 58
// DESCRIPTION:	reverse

void reverse(char s[]) {
    int c, i, j;
    for (i = 0, j = strlen(s) - 1; i < j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}

int main(int argc, char *argv[]) {
    char text[] = "buna dimineata!";
    reverse(text);
    printf("[ OUT ] %s\n", text);
    return 0;
}
