#include <stdio.h>

// COMPILE:	gcc syntax039.c
// USAGE:	./a.out text1 text2
// BOOKMARK:	pg 46 ex 2-4
// DESCRIPTION: remove all occurances of chars from text2 in text1

void small_squeze(char s[], char c);
void big_squeze(char s[], char t[]);

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("[ LOG ] illegal arguments, usage: ./a.out text1 text2");
        return 1;
    }
    char *text1 = argv[1];
    char *text2 = argv[2];
    big_squeze(text1, text2);

    printf("[ OUT ] %s\n", text1);
    return 0;
}

void small_squeze(char s[], char c) {
    int i, j;
    for (i = j = 0; s[i] != '\0'; i++)
        if (s[i] != c)
            s[j++] = s[i];
    s[j] = '\0';
}

void big_squeze(char s[], char t[]) {
    int i = 0;
    char c;
    while ((c = t[i++]) != '\0') {
        small_squeze(s, c);
    }
}

