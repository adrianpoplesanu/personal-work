// COMPILE:     gcc syntax099.c
// USAGE:       ./a.out
// BOOKMARK:    pg 94
// DESCRIPTION: string arrays are mutable, string pointers are not mutable

#include <stdio.h>

void change_supported(char str[]) {
    str[1] = 'b';
}

void change_not_supported(char *str) {
    str[1] = 'b';
}

int main(int argc, char *argv[]) {
    char text[] = "buna dimineata!";
    change_supported(text);
    printf("[ LOG ] %s\n", text);

    char *message = "ala bala portocala!";
    change_not_supported(message);
    printf("[ LOG ] %s\n", message);
    return 0;
}