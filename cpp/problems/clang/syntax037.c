#include <stdio.h>

// COMPILE:	gcc syntax037.c
// USAGE:	./a.out texts e
// BOOKMARK:	pg 45
// DESCRIPTION:	remove all occurences of a character

void squeeze(char s[], int c);

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("[ ILLEGAL ARGUMENTS ] usage: ./a.out text char-to-be-removed, ex: ./a.out texts e\n");
        return 1;
    }
    char *text = argv[1];
    char *c = argv[2];

    if (c[1] != '\0') {
        printf("[ ILLEGAL ARGUMENTS ] usage: ./a.out text char-to-be-removed, ex: ./a.out texts e\n");
        return 1;
    }

    squeeze(text, c[0]);
    printf("[ OUT ] %s\n", text);
    return 0;
}

void squeeze(char s[], int c) {
    int i, j;
    for (i = j = 0; s[i] != '\0'; i++)
        if (s[i] != c)
            s[j++] = s[i];
    s[j] = '\0';
}
