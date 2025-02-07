// COMPILE:     gcc syntax106.c
// USAGE:       ./a.out
// BOOKMARK:    pg 96 ex 5-4
// DESCRIPTION: strend with pointers

#include <stdio.h>

int my_strend(char *s, char *t) {
    char *currentSource  = s;
    char *currentTarget = t;
    while (*currentSource != '\0') {
        for (; *currentSource == *currentTarget; currentSource++, currentTarget++) if (*currentSource == '\0' && *currentTarget == '\0') return 1;
        currentSource = s++;
        currentTarget = t;
    }
    return 0;
}

int main(int argc, char *argv[]) {
    char *s = "buna dimineata!";
    //char *s = "buna dimineata!a";
    char *t = "dimineata!";
    int result = my_strend(s, t);
    printf("[ LOG ] %d\n", result);
    return 0;
}