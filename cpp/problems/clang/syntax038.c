#include <stdio.h>

// COMPILE:	gcc syntax038.c
// USAGE:	./a.out text1 text2
// BOOKMARK:	pg 46
// DESCRIPTION:	my own strcat implementation

void my_strcat(char s[], char t[]);

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("USAGE EXAMPLE: ./a.out text1 text2\n");
        return 1;
    }
    char* s = argv[1];
    char* t = argv[2];
    my_strcat(s, t);

    printf("[ LOG ] %s\n", s);
    return 0;
}

void my_strcat(char s[], char t[]) {
    int i = 0, j = 0;
    while(s[i] != '\0') i++;
    while((s[i++] = t[j++]) != '\0') ;
}
