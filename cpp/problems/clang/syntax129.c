// COMPILE:     gcc syntax129.c
// USAGE:       cat input_syntax129.txt | ./a.out -nr
// BOOKMARK:    pg 108
// DESCRIPTION: ex 5-14

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXLEN 		1000
#define MAXLINES	5000
char *lineptr[MAXLINES];
int nlines;

int readlines(char *lineptr[], int nlines);

void my_qsort(void *lineptr[], int left, int right,
              int (*comp)(void *, void *), int reverse);
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

int my_strcmp(char *s, char *t) {
    //printf("[ LOG ] comparing %s with %s\n", s, t);
    for (; *s == *t; s++, t++) if (*s == '\0') return 0;
    int result = *s - *t;
    //printf("[ LOG ] result %d\n", result);
    if (result < 0) return -1;
    if (result > 0) return 1;
    return 0;
}

int my_numcmp(char *s, char *t) {
    double v1, v2;
    v1 = atof(s);
    v2 = atof(t);
    if (v1 < v2) return -1;
    if (v1 > v2) return 1;
    return 0;
}

void swap(int i, int j) {
    //printf("[ LOG ] swapping %s with %s\n", lineptr[i], lineptr[j]);
    char *aux = lineptr[i];
    lineptr[i] = lineptr[j];
    lineptr[j] = aux;
}

void print_lines() {
    int i;
    for (i = 0; i < nlines; i++) {
        printf("[ RESULT ] %s\n", lineptr[i]);
    }
}

int pivot(int left, int mid, int right, int reverse) {
    int i = left, last = left;
    swap(left, mid);
    for (int i = left + 1; i <= right; i++) {
        if (reverse == 0) {
            if (my_strcmp(lineptr[i], lineptr[left]) < 0) {
                swap(++last, i);
            }
        } else {
            if (my_strcmp(lineptr[i], lineptr[left]) > 0) {
                swap(++last, i);
            }
        }
    }
    swap(left, last);
    return last;
}

void my_qsort(void *lineptr[], int left, int right, int (*comp)(void *, void *), int reverse) {
    if (left < right) {
        int mid = (left + right) / 2;
        int p = pivot(left, mid, right, reverse);
        my_qsort(lineptr, left, p - 1, comp, reverse);
        my_qsort(lineptr, p + 1, right, comp, reverse);
    }
}

void sort_lines() {
    my_qsort((void **)lineptr, 0, nlines - 1, (int (*)(void*,void*)) my_strcmp, 0);
}

int main(int argc, char *argv[]) {
    int c, numeric = 0, reverse = 0;
    while (--argc > 0 && (*++argv)[0] == '-') {
        while ((c = *++argv[0])) {
            switch(c) {
                case 'n':
                    numeric = 1;
                    break;
                case 'r':
                    reverse = 1;
                    break;
                default:
                    printf("usage: illegal option %c\n", c);
                    argc = 0;
                    numeric = -1;
                    break;
            }
        }
    }
    printf("[ LOG ] numeric=%d reverse=%d\n", numeric, reverse);

    if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
        printf("[ LOG ] successfully read %d lines\n", nlines);
        if (numeric) {
            my_qsort((void **)lineptr, 0, nlines - 1, (int (*)(void*,void*)) my_numcmp, reverse);
        } else {
            my_qsort((void **)lineptr, 0, nlines - 1, (int (*)(void*,void*)) my_strcmp, reverse);
        }
        print_lines();
        /*int i = 0;
        while (i < nlines) {
            printf("%s\n", lineptr[i++]);
        }*/
    } else {
        printf("error: input too big\n");
        return 1;
    }
    return 0;
}

