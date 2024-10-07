#include <stdio.h>

// COMPILE:	gcc syntax034.c
// USAGE:	./a.out 2024
// BOOKMARK:	pg 41
// DESCRIPTION:	transform a string into coresponding int value

int atoi(char s[]);

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("[ LOG ] illegal number of arguments\n");
        return 1;
    }

    int value = atoi(argv[1]);
    printf("[ LOG ] read arg value: %d\n", value);
    return 0;
}

int atoi(char s[]) {
    int i, n;

    n = 0;
    for (i = 0; s[i] >= '0' && s[i] <= '9'; ++i) {
        n = 10 * n + (s[i] - '0');
    }
    return n;
}
