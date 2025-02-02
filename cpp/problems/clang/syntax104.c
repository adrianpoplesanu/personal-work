// COMPILE:     gcc syntax104.c
// USAGE:       ./a.out
// BOOKMARK:    pg 95
// DESCRIPTION: my strcmp implementation #1

#include <stdio.h>

int my_strcmp(char *s, char *t) {
    int i;
    for(i = 0; s[i] == t[i]; i++) if (s[i] == '\0') return 0;
    return s[i] - t[i];
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