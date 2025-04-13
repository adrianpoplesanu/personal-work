// COMPILE:     gcc syntax125.c
// USAGE:       cat syntax123.c | ./a.out -11
// BOOKMARK:    pg 106
// DESCRIPTION: my own unoptimized implementation of tail -n
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXLINE 1000
#define MAXRESULT 1000

int my_getline(char line[], int maxline);

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: ./a.out -11\n");
        return 1;
    }
    char *param = argv[1];
    if (param[0] != '-') {
        printf("Wrong param: expectig -123\n");
        return 1;
    }
    int i = 1, number = 0;
    while(param[i] != '\0') {
        if (isdigit(param[i])) {
            number = number * 10 + (param[i] - '0');
            i++;
        }
    }
    int len, pos = 0;
    char line[MAXLINE];
    char* results[MAXRESULT];
    while((len = my_getline(line, MAXLINE)) > 0) {
        char* p = (char*) malloc(len * sizeof(char));;
        line[len-1] = '\0';  /* delete newline */
        strcpy(p, line);
        results[pos++] = p;
        if (pos > number) {
            int j;
            char *to_delete = results[0];
            for (j = 0; j < pos; j++) {
                results[j] = results[j + 1];
            }
            pos--;
            free(to_delete);
        }
        //printf("%s", line]);
        //printf("%d - %s", pos - 1, results[pos - 1]);
    }
    for (i = 0; i < pos; i++) {
        printf("%s\n", results[i]);
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
