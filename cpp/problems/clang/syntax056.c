#include <stdio.h>
#include <ctype.h>

// COMPILE:	gcc syntax056.c
// USAGE:	./a.out
// BOOKMARK:	pg 57
// DESCRIPTION: custom atoi implementation

int my_atoi(char s[]) {
    int i, n, sign;
    for (i = 0; isspace(s[i]); i++) ;
    sign = (s[i] == '-') ? -1 : 1;
    if (s[i] == '+' || s[i] == '-') i++;
    for (n = 0; isdigit(s[i]); i++) {
        n = 10 * n + (s[i] - '0');
    }
    return sign * n;
}

int main(int argc, char *argv[]) {
    char s[10] = "3435";
    int val = my_atoi(s);
    printf("%d\n", val);
    return 0;
}
