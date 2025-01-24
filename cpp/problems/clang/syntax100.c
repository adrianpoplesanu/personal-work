// COMPILE:     gcc syntax100.c
// USAGE:       ./a.out
// BOOKMARK:    pg 94
// DESCRIPTION: strcpy #1 implementation

#include <stdio.h>

void my_strcpy(char *s, char *t) {
    int i = 0;

    while((s[i] = t[i]) != '\0') i++;
}

int main(int argc, char *argv[]) {
    char s[30];
    char t[30] = "buna dimineata!";
    my_strcpy(s, t);
    printf("[ LOG ] %s\n", s);
    return 0;
}