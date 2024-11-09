#include <stdio.h>

// COMPILE:	gcc syntax055.c
// USAGE:	./a.out
// BOOKMARK:	pg 56 ex 3-2
// DESCRIPTION:	convert escape sequences to characters

void escape(char s[], char t[]) {
    int i = 0, j = 0;
    while (t[i] != '\0') {
        if (t[i] == '\\') {
            i++;
            switch(t[i]) {
                case 'n':
                    s[j++] = '\n';
                break;
                case 't':
                    s[j++] = '\t';
                break;
                default:
                    s[j++] = '\\';
                    s[j++] = t[i];
                break;
            }
        } else {
            s[j++] = t[i];
        }
        i++;
    }
    s[j] = '\0';
}

int main(int argc, char *argv[]) {
    char s[20], t[20] = "abcd\\tefg";
    escape(s, t);
    printf("%s\n", s);
    return 0;
}
