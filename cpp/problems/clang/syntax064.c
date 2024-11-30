#include <stdio.h>
#include <string.h>

// COMPILE:	gcc syntax064.c
// USAGE:	./a.out
// BOOKMARK:	pg 60
// DESCRIPTION: trim

int trim(char s[]) {
    int n;

    for (n = strlen(s) - 1; n >= 0; n--) {
        if (s[n] != ' ' && s[n] != '\t' && s[n] != '\n') {
            break;
        }
    }
    s[n + 1] = '\0';
    return n;
}

int main(int argc, char *argv[]) {
    char s[] = "buna dimineata   	";
    trim(s);
    printf("[ out ] ###%s###\n", s);
    return 0;
}
