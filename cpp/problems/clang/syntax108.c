// COMPILE:     gcc syntax106.c
// USAGE:       ./a.out
// BOOKMARK:    pg 96 ex 5-5
// DESCRIPTION: my strncpy, my strncat, my strncmp

#include <stdio.h>

void my_strncpy(char *s, char *t, int n) {
    int i = 0;
    while(i++ < n && (*s++ = *t++)) ;
}

void my_strncat(char *destination, char *source, int n) {
    int i = 0;
    while(*destination != '\0') *destination++;
    while(i++ < n && (*destination++ = *source++)) ;
    *destination = '\0';
}

int my_strncmp(char *s, char *t, int n) {
    int i = 0;
    for (; i < n && *s == *t; s++, t++) if (*s == '\0') return 0;
    int result = *s - *t;
    if (result < 0) return -1;
    if (result > 0) return 1;
    return 0;
}

void test_my_strncpy() {
    char s[] = "aaaa dimineata!";
    char t[] = "buna-seara!";
    my_strncpy(s, t, 5);
    printf("[ LOG ] my_strncpy: %s\n", s);
}

void test_my_strncat() {
    char s[] = "aaaa dimineata!";
    char t[] = "buna-seara!";
    my_strncat(s, t, 7);
    printf("[ LOG ] my_strncat: %s\n", s);
}

void test_my_strncmp() {
    char s[] = "aaaa dimineata!";
    char t[] = "aaaa seara!";
    int result = my_strncmp(s, t, 7);
    printf("[ LOG ] my_strncmp: %d\n", result);
}

int main(int argc, char *argv[]) {
    test_my_strncpy();
    test_my_strncat();
    test_my_strncmp();
    return 0;
}