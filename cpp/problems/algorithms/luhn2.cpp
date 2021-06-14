#include <iostream>

int digit_calculator(char *cc) {
    int f = 2, s = 0;
    for (int i = 14; i > -1; i--) {
        int v = (cc[i] - '0') * f;
        if (v < 10) s += v;
        else s += v - 9;
        if (f == 2) f = 1;
        else f = 2;
    }
    return (s * 9) % 10;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cout << "Usage: ./luhn 123456789012345 - first 15 digits of creditcard\n";
        return 1;
    }

    char *credit_card = argv[1];
    if(strlen(credit_card) != 15) {
        std::cout << "Invalid input: needs to be 15 digits\n";
        return 1;
    }

    std::cout << digit_calculator(credit_card) << "\n";
    return 0;
}
