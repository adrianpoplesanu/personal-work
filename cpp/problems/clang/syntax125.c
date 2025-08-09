// COMPILE:     gcc syntax125.c
// USAGE:       cat input_syntax125.txt | ./a.out -xn pattern location
// BOOKMARK:    pg 106
// DESCRIPTION: ex 5-13

#include <stdio.h>
#include <string.h>

#define MAXLEN 1000
#define MAXLINES	5000
char *lineptr[MAXLINES];

int readlines(char *lineptr[], int nlines);

void qsort(void *lineptr[], int left, int right,
           int (*comp)(void *, void *));
int numcmp(char *, char *);

#define ALLOCSIZE   10000 /* size of available space */

static char allocbuf[ALLOCSIZE]; /* storage */
static char *allocp = allocbuf; /* next free position */

void my_strcpy(char *s, char *t) {
    int i = 0;

    while((s[i] = t[i]) != '\0') i++;
}

char* alloc(int n) {
    if (allocbuf + ALLOCSIZE - allocp >= n) {
        allocp += n;
        return allocp - n;  /* old p */
    }
    return 0;
}

int my_getline(char s[], int lim) {
    int c, i;
    i = 0;
    while(--lim > 0 && (c=getchar()) != EOF && c != '\n') {
        s[i++] = c;
    }
    if (c == '\n') {
        s[i++] = c;
    }
    s[i] = '\0';
    return i;
}

int readlines(char *lineptr[], int maxlines) {
    int len, nlines;
    char *p, line[MAXLEN];

    nlines = 0;
    while((len = my_getline(line, MAXLEN)) > 0) {
        if (nlines >= maxlines || ((p = alloc(len)) == NULL)) {
            return -1;
        } else {
            line[len - 1] = '\0';
            my_strcpy(p, line);
            lineptr[nlines++] = p;
        }
    }
    return nlines;
}

int main(int argc, char *argv[]) {
    printf("running...\n");
    return 0;
}

