#include <stdio.h>

// COMPILATION:	gcc syntax028.c
// USAGE:	cat syntax028.c | ./a.out
// BOOKMARK: 	pg 31 ex 1-19
// TESTING:	

#define MAXLINE 1000

int my_getline(char line[], int maxline);
void reverse(char line[], char out[], int size);

int main() {
    int len;
    int max;
    char line[MAXLINE];
    char reversed[MAXLINE];

    while((len = my_getline(line, MAXLINE)) > 0) {
        reverse(line, reversed, len);
        printf("%s\n", reversed);
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

void reverse(char line[], char out[], int size) {
    int i, end = 0;
    for (i = 0; i < size - 1; ++i) {
        out[size - 1 - i - 1] = line[i];
    }
    out[size - 1] = '\0';
}
