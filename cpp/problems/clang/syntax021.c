#include <stdio.h>

// COMPILATION: gcc syntax021.c
// USAGE: 	./a.out
// BOOKMARK: 	pg 28 ex 1.15

float fahr_to_celsius(float fahr) {
    return 5.0 * (fahr - 32.0) / 9.0;
}

int main() {
    float fahr, celsius;
    float lower, upper, step;

    lower = 0;
    upper = 300;
    step = 20;

    fahr = lower;
    while (fahr <= upper) {
        celsius = fahr_to_celsius(fahr);
        printf("%3.0f %6.1f\n", fahr, celsius);
        fahr = fahr + step;
    }
    return 0;
}
