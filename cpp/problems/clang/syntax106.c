// COMPILE:     gcc syntax106.c
// USAGE:       ./a.out
// BOOKMARK:    pg 96 ex 5-3
// DESCRIPTION: strcat with pointers

#include <stdio.h>

void my_strcat(char *s, char *t) {
    while(*s++ != '\0') ;
    s--;
    while((*s++ = *t++)) ;
}

int main(int argc, char *argv[]) {
    // daca fac declaratia cu char *s atunci primesc bus error
    char s[] = "buna";
    char t[] = " dimineata!";
    my_strcat(s, t);

    printf("[ LOG ] %s\n", s);
    return 0;
}