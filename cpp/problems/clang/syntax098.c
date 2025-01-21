// COMPILE:	gcc syntax098.c
// USAGE:	./a.out
// BOOKMARK:	pg 92
// DESCRIPTION	yet another version of strlen

#include <stdio.h>

int my_strlen(char *s) {
    char *p = s;
    while(*p != '\0') p++;
    return p - s;
}

int main(int argc, char *argv[]) {
    char s[] = "buna dimineata!";
    int size = my_strlen(s);
    printf("[ LOG ] %d\n", size);
    return 0;
}
