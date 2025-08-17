// COMPILE:     gcc syntax125.c
// USAGE:       cat input_syntax125.txt | ./a.out -10
// BOOKMARK:    pg 106
// DESCRIPTION: ex 5-13

#include <stdio.h>
#include <string.h>

#define MAXLEN 		1000
#define MAXLINES	5000
char *lineptr[MAXLINES];

int readlines(char *lineptr[], int nlines);

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
    int c, except = 0, number = 0, found = 0;
    while (--argc > 0 && (*++argv)[0] == '-') {
        while ((c = *++argv[0])) {
            switch(c) {
                case 'x':
                    except = 1;
                    break;
                //case 'n':
                //    number = 1;
                //    break;
                case '0':
                case '1':
                case '2':
                case '3':
                case '4':
                case '5':
                case '6':
                case '7':
                case '8':
                case '9':
                    printf("[ LOG ] c = %d\n", c - '0');
                    number = number * 10 + c - '0';
                    break;
                default:
                    printf("usage: illegal option %c\n", c);
                    argc = 0;
                    found = -1;
                    break;
            }
        }
    }
    printf("[ LOG ] except=%d number=%d found=%d\n", except, number, found);

    int nlines;
    if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
        printf("successfully read %d lines\n", nlines);
        int i = nlines - number >= 0 ? nlines-number : 0;
        while (i < nlines) {
            printf("%s\n", lineptr[i++]);
        }
    } else {
        printf("error: input too big\n");
        return 1;
    }
    return 0;
}

