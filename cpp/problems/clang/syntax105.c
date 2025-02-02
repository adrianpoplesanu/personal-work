// COMPILE:     gcc syntax105.c
// USAGE:       ./a.out
// BOOKMARK:    pg 95
// DESCRIPTION: my strcmp implementation #2

#include <stdio.h>

int my_strcmp(char *s, char *t) {
    for (; *s == *t; s++, t++) if (*s == '\0') return 0;
    return *s - *t;
}

int main(int argc, char *argv[]) {
    int result1 = my_strcmp("aaab", "aaac");
    printf("[ LOG ] %d\n", result1);

    int result2 = my_strcmp("aaac", "aaab");
    printf("[ LOG ] %d\n", result2);

    int result3 = my_strcmp("aaaa", "aaaa");
    printf("[ LOG ] %d\n", result3);

    return 0;
}