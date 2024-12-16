// COMPILE:	gcc syntax072.c
// USAGE:	./a.out
// BOOKMARK:	pg 65 ex 4-1
// DESCRIPTION: strindex return rightmost occurence

#include <stdio.h>

int old_strindex(char s[], char t[]) {
    int i, j, k, result = -1;

    for (i = 0; s[i] != '\0'; i++) {
        for (j = i, k = 0; t[k] != '\0' && s[j] == t[k]; j++, k++)
            ;
        if (k > 0 && t[k] == '\0') {
            return i;
        }
    }
    return -1;
}

int strindex(char s[], char t[]) {
    int i, j, k, result = -1;

    for (i = 0; s[i] != '\0'; i++) {
        for (j = i, k = 0; t[k] != '\0' && s[j] == t[k]; j++, k++)
            ;
        if (k > 0 && t[k] == '\0') {
            result = i;
        }
    }
    return result;
}

int main(int argc, char *argv[]) {
    char s[] = {"abc abc"};
    char t[] = {"abc"};

    printf("%d\n", old_strindex(s, t));
    printf("%d\n", strindex(s, t));
    return 0;
}
