// COMPILE:     gcc syntax103.c
// USAGE:       ./a.out
// BOOKMARK:    pg 95
// DESCRIPTION: strcpy #4 implementation

#include <stdio.h>

void my_strcpy(char *s, char *t) {
    while((*s++ = *t++)) ;
}

int main(int argc, char *argv[]) {
    char s[30];
    char t[30] = "buna dimineata!";
    my_strcpy(s, t);
    printf("[ LOG ] %s\n", s);
    return 0;
}