// COMPILE:	gcc syntax075.c
// USAGE:	./a.out
// BOOKMARK:	pg 66
// DESCRIPTION:	my atoi

#include <stdio.h>
#include <ctype.h>

#define MAXLINE 100

double my_atof(char s[]) {
    double val, power;
    int i, sign;

    for(i = 0; isspace(s[i]); i++)
        ;

    sign = (s[i] == '-') ? -1 : 1;
    if (s[i] == '+' || s[i] == '-') {
        i++;
    }

    for (val = 0.0; isdigit(s[i]); i++) {
        val = 10.0 * val + (s[i] - '0');
    }

    if (s[i] == '.') {
        i++;
    }

    for (power = 1.0; isdigit(s[i]); i++) {
        val = 10.0 * val + (s[i] - '0');
        power *= 10;
    }
    return sign * val / power;
}

int my_atoi(char s[]) {
    double my_atof(char s[]);
    return (int) my_atof(s);
}

int main(int argc, char *argv[]) {
    int result = my_atoi("123");
    printf("[ LOG ] %i\n", result);
}
