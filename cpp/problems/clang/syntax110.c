// COMPILATION:		gcc syntax110.c
// USAGE:		echo "aaa bbb" | ./a.out
// BOOKMARK:		n/a
// DESCRIPTION:		reading words from stdin and storing them in an array of char pointers

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXLINES 1000
char *lineptr[MAXLINES];
int nlines = 0;

void read_lines() {
    char input[100];
    while(scanf("%99s", input) != EOF) {
        char *word = (char*)malloc(100 * sizeof(char));
        strncpy(word, input, 100);
        lineptr[nlines++] = word;
    }
}

void print_lines() {
    int i;
    for (i = 0; i < nlines; i++) {
        printf("[ LOG ] %s\n", lineptr[i]);
    }
}

int main(int argc, char *argv[]) {
    read_lines();
    print_lines();
    return 0;
}
