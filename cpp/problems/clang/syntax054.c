#include <stdio.h>

// COMPILE:	gcc syntax054.c
// USAGE:	./a.out
// BOOKMARK:	pg 56 ex 3-2
// DESCRIPTION:	convert characters to escape sequences

void escape(char s[], char t[]) {
    int i = 0, j = 0;
    while (t[i] != '\0') {
        switch(t[i]) {
            case '\n':
               s[j++] = '\\';
               s[j++] = 'n';
            break;
            case '\t':
               s[j++] = '\\';
               s[j++] = 't';
            break;
            default:
               s[j++] = t[i];
            break;
        }
        i++;
    }
    s[j] = '\0';
}

int main(int argc, char *argv[]) {
    char s[20], t[20] = "abcd	efg";
    escape(s, t);
    printf("%s\n", s);
    return 0;
}
