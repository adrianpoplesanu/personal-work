#include <stdio.h>

// COMPILATION:	gcc syntax031.c
// USAGE:	./a.out
// BOOKMARK:	pg 38.
// DESCRIPTION:	custom strlen implementation

int my_strlen(char s[]);

int main() {
    char *test = "buna dimineata!";
    int size = my_strlen(test);
    printf("%d\n", size);
    return 0;
}

int my_strlen(char s[]) {
    int i;
    while (s[i] != '\0') ++i;
    return i;
}
