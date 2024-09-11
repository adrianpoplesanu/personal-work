#include <stdio.h>

// COMPILATION:	gcc syntax026.c
// USAGE:	cat syntax026.c | ./a.out
// BOOKMARK:	pg 31 ex 1-17

#define MAXLINE 1000

int my_getline(char line[], int maxline);

int main() {
    int len;
    int max;
    char line[MAXLINE];
    char longest[MAXLINE];

    while((len = my_getline(line, MAXLINE)) > 0) {
        if (len > 80) {
            printf("%s", line);
        }
    }

    return 0;
}

int my_getline(char s[], int lim) {
    int c, i;
    for (i = 0; i < lim - 1 && (c=getchar()) != EOF && c != '\n'; ++i) s[i] = c;
    if (c == '\n') {
        s[i] = c;
        ++i;
    }
    s[i] = '\0';
    return i;
}

