// COMPILE:	gcc syntax084.c
// USAGE:	./a.out
// BOOKMARK:	pg 79 ex 4-13
// DESCRIPTION:	recursive string reverse

#include <stdio.h>

void reverse(char s[]) {
    static int i = 0;
    static int j = 0;

    if (s[i] != '\0') {
        char temp = s[i++];
        reverse(s);
        s[j++] = temp;
    }

    if (s[j] == '\0') {
        i = 0;
        j = 0;
    }
}

int main(int argc, char *argv[]) {
    char s[] = "abc";
    reverse(s);
    printf("%s\n", s);
    return 0;
}
