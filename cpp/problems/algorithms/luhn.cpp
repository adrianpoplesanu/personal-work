#include <iostream>
using namespace std;

void luhn(char *cc) {
    int s = 0, f = 2;
    for (int i = 14; i > -1; i--) {
        int v = (cc[i] - '0') * f;
        if (v < 10) s += v;
        else s+= v - 9;
        if (f == 2) f = 1;
        else f = 2;
    }
    cout << (s * 9) % 10 << endl;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        cout << "Usage: ./lunh 123456789012345 - first 15 digits of credit card" << endl;
        return 1;
    }

    char *credit_card = argv[1];
    if (strlen(credit_card) != 15) {
        cout << "Invalid 15 number digit for credit card check" << endl;
        return 1;
    }
    cout << "Calculating check sum digit for: " << credit_card << endl;
    luhn(credit_card);
    return 0;
}
