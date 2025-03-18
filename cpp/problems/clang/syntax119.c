// COMPILE:     gcc syntax118.c
// USAGE:       ./a.out pattern
// BOOKMARK:    pg 104
// DESCRIPTION: find pattern

#include <stdio.h>
#include <string.h>

#define MAXLINE	100

int my_getline(char s[], int lim);

int main(int argc, char *argv[]) {
    //char line[MAXLINE];
    char *line = NULL;
    size_t size;
    //while(my_getline(line, MAXLINE) > 0) {
    while(getline(&line, &size, stdin) > 0) {
	printf("[ LINE ] %s\n", line);
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
    //printf("[ LOG ] %d\n", i); // daca i e 1 atunci nu a luat decat un enter gol, as putea sa ies
    return i;
}

