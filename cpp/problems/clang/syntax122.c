// COMPILE:     gcc syntax122.c
// USAGE:       ./a.out pattern
// BOOKMARK:    pg 104
// DESCRIPTION: find pattern

#include <stdio.h>
#include <string.h>

#define MAXLINE 1000

int main(int argc, char *argv[]) {
    //char line[MAXLINE];
    char *line = NULL;
    int found = 0;
    size_t size;

    if (argc != 2) {
        printf("Usage: find pattern\n");
    } else {
        while (getline(&line, &size, stdin) > 0) {
            if (strstr(line, argv[1]) != NULL) {
                printf("[ MATCH ] %s", line);
                found++;
            }
        }
    }
    return 0;
}
