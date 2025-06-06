#include <stdio.h>

// COMPILE:	gcc syntax050.c
// USAGE:	./a.out
// BOOKMARK:	pg 49
// DESCRIPTION:	conver upper to lower case

int lower(int c);

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("[ LOG ] illegal number of arguments\n");
        return 1;
    }

    int j = 1;
    while (j < argc) {
        char *word = argv[j++];
        int i = 0;
        while(word[i] != '\0') {
            word[i] = lower(word[i]);
            ++i;
        }
        printf("[ LOG ] %s\n", word);
    }
    return 0;
}

int lower(int c) {
    return (c >= 'A' && c <= 'Z') ? c + 'a' - 'A' : c;
}
