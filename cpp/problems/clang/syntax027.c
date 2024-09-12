#include <stdio.h>

// COMPILATION:	gcc syntax027.c
// USAGE:	cat syntax027.c | ./a.out
// BOOKMARK: 	pg 31 ex 1-18
// TESTING:	

#define MAXLINE 1000

int my_getline(char line[], int maxline);
void clean_line(char line[], char out[], int size);

int main() {
    int len;
    int max;
    char line[MAXLINE];
    char cleaned[MAXLINE];

    while((len = my_getline(line, MAXLINE)) > 0) {
        clean_line(line, cleaned, len);
        if (cleaned[0] != '\0') printf("%s\n", cleaned);
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

void clean_line(char line[], char out[], int size) {
    int i, end = 0;
    for (i = 0; i < size; ++i) {
        if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n') {
            end = i;
        }
    }
    i = 0;
    if (end > 0) {
        for (; i <= end; ++i) out[i] = line[i];
    }
    out[i] = '\0';
}
