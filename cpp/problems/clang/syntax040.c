#include <stdio.h>

// COMPILE:	gcc syntax040.c
// USAGE:	./a.out text1 text2
// BOOKMARK:	pg 46 ex 2-5
// DESCRIPTION:	return index of first character in text1 from text2

int find_first(char s[], char t[]);
int find_character(char s[], char c);

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("[ LOG ] illegal arguments, usage: ./a.out text1 text2");
    }
    char *text1 = argv[1];
    char *text2 = argv[2];

    int pos = find_first(text1, text2);
    printf("[ OUT ] %d\n", pos);
    return 0;
}

int find_first(char s[], char t[]) {
    int i = 0, index = -1;
    char c;
    while((c = t[i++]) != '\0') {
        int pos = find_character(s, c);
        if (pos > -1 && (pos < index || index == -1)) index = pos; 
    }
    return index;
}

int find_character(char s[], char c) {
    int j = 0;
    char crt;
    while((crt = s[j++]) != '\0') {
        if (crt == c) return j - 1;
    }
    return -1;
}
