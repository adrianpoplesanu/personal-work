// COMPILE:	gcc syntax095.c
// USAGE:	./a.out
// BOOKMARK:	pg 89
// DESCRIPTION	pointer implementation of strlen

#include <stdio.h>

int my_strlen(char *s) {
    int n;
    for (n = 0; *s != '\0'; s++) n++;
    return n;
}

int main(int argc, char *argv[]) {
    char s[] = "buna dimineata!";
    int size = my_strlen(s);
    printf("[ LOG ] %d\n", size);
    return 0;
}
