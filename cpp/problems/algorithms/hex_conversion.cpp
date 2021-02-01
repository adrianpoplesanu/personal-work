#include <iostream>
using namespace std;

int get_digit_value(char ch) {
    int digit = 0;
    switch(ch) {
        case '0': digit = 0; break;
        case '1': digit = 1; break;
        case '2': digit = 2; break;
        case '3': digit = 3; break;
        case '4': digit = 4; break;
        case '5': digit = 5; break;
        case '6': digit = 6; break;
        case '7': digit = 7; break;
        case '8': digit = 8; break;
        case '9': digit = 9; break;
        case 'a': digit = 10; break;
        case 'b': digit = 11; break;
        case 'c': digit = 12; break;
        case 'd': digit = 13; break;
        case 'e': digit = 14; break;
        case 'f': digit = 15; break;
    }
    return digit;
}

int convert(char *hex) {
    int size = 0;
    while(hex[size] != '\0') {
        size++;
    }
    int number = 0, factor = 1;
    for (int i = size - 1; i >= 0; --i) {
        number += get_digit_value(hex[i]) * factor;
        factor *= 16;
    }
    return number;
}

int main (int argc, char *argv[]) {
    int a = 0xf00d;
    cout << a << "\n";

    char hex[10] = "f00d";
    cout << convert(hex) << "\n";

    return 0;
}
