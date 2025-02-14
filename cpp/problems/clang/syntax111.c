// COMPILE:		gcc syntax111.c
// USAGE:		echo "fff aaa eee bbb ccc" | ./a.out
// BOOKMARK:		n/a
// DESCRIPTION:		reading words from stdin and storing them in an array of char pointers and sorting them

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXLINES 1000
#define MAX_WORD_SIZE 100
char *lineptr[MAXLINES];
int nlines = 0;

int my_strcmp(char *s, char *t) {
    //printf("[ LOG ] comparing %s with %s\n", s, t);
    for (; *s == *t; s++, t++) if (*s == '\0') return 0;
    int result = *s - *t;
    //printf("[ LOG ] result %d\n", result);
    if (result < 0) return -1;
    if (result > 0) return 1;
    return 0;
}

void swap(int i, int j) {
    //printf("[ LOG ] swapping %s with %s\n", lineptr[i], lineptr[j]);
    char *aux = lineptr[i];
    lineptr[i] = lineptr[j];
    lineptr[j] = aux;
}

void read_lines() {
    char input[MAX_WORD_SIZE];
    while(scanf("%99s", input) != EOF) {
        char *word = (char*)malloc(MAX_WORD_SIZE * sizeof(char));
        strncpy(word, input, MAX_WORD_SIZE);
        lineptr[nlines++] = word;
    }
}

void print_lines() {
    int i;
    printf("[ RESULT ] ");
    for (i = 0; i < nlines; i++) {
        printf("%s ", lineptr[i]);
    }
    printf("\n");
}

int pivot(int left, int mid, int right) {
    int i = left, last = left;
    swap(left, mid);
    for (int i = left + 1; i <= right; i++) {
        if (my_strcmp(lineptr[i], lineptr[left]) < 0) {
            swap(++last, i);
        }
    }
    swap(left, last);
    return last;
}

void my_qsort(int left, int right) {
    if (left < right) {
        int mid = (left + right) / 2;
        int p = pivot(left, mid, right);
        my_qsort(left, p - 1);
        my_qsort(p + 1, right);
    }
}

void sort_lines() {
    my_qsort(0, nlines - 1);
}

int main(int argc, char *argv[]) {
    read_lines();
    sort_lines();
    print_lines();
    return 0;
} 
