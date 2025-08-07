// COMPILE:     gcc syntax107.c
// USAGE:       cat input_syntax109.txt | ./a.out
// BOOKMARK:    pg 97
// DESCRIPTION: qsort strings

#include <stdio.h>

#define MAXLINES 5000
#define MAXLEN 1000

char *lineptr[MAXLINES];

#define ALLOCSIZE   10000 /* size of available space */

static char allocbuf[ALLOCSIZE]; /* storage */
static char *allocp = allocbuf; /* next free position */

char* alloc(int n) {
    if (allocbuf + ALLOCSIZE - allocp >= n) {
        allocp += n;
        return allocp - n;  /* old p */
    }
    return 0;
}

void my_strcpy(char *s, char *t) {
    int i = 0;

    while((s[i] = t[i]) != '\0') i++;
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
    int nlines;
    if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
        printf("successfully read %d lines\n", nlines);
        int i = 0;
        while (i < nlines) {
            printf("%s\n", lineptr[i++]);
        }
    } else {
        printf("error: input too big to sort\n");
        return 1;
    }
    return 0;
}
