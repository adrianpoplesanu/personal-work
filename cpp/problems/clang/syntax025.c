#include <stdio.h>

// COMPILATION:	gcc syntax025.c
// USAGE:	cat syntax025.c | ./a.out
// BOOKMARK:	pg 31 ex 1-16

#define MAXLINE 1000

int my_getline(char line[], int maxline);

int main() {
    int len;
    int max;
    int total;
    char line[MAXLINE];
    char longest[MAXLINE];

    total = 0;
    while((len = my_getline(line, MAXLINE)) > 0) {
        printf("%d\n", len);
        total += len;
    }

    if (total > 0) printf("%d\n", total);

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

