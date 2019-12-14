#include <iostream>
#include <iomanip>
#include "big_number.h"
using namespace std;

void running(void) {
    cout << "\033[29;1mrunning\033[0m \033[35;1mBig Number ver 1.13\033[0m..." << endl;
}

BigNumber::BigNumber() : baza(BAZA_DEFAULT), _len(MAX_CIFRE) {
    for (int i = 0; i < _len; i++) {
        cifre[i] = 0;
    }
}

BigNumber::BigNumber(int n) : baza(BAZA_DEFAULT), _len(MAX_CIFRE) {
    LoadFromInt(n);
}

BigNumber::BigNumber(string s) : baza(BAZA_DEFAULT), _len(MAX_CIFRE) {
    LoadFromString(s);
}

BigNumber::~BigNumber() {

}

void BigNumber::LoadFromString(string s) {
    int b = baza, size = 0;
    while(b > 1) {
        b /= 10;
        size++;
    }
    int _len = s.length();
    int start = _len - size;
    int i = 0;
    while(start >= 0) {
        cifre[i] = stoi(s.substr(start, size));
        i++;
        start -= size;
        if (start < 0 && start > -size) {
            cifre[i] = stoi(s.substr(0, size + start));
            return;
        }
    }
    if (start < 0 && start > -size) { // if the string converter to BigNumber is one "digit"
        cifre[0] = stoi(s.substr(0, size + start));
    }
}

void BigNumber::LoadFromInt(int n) {

}

void BigNumber::Add(BigNumber number) {
    int suma[_len];
    for (int i = 0; i < _len; i++) suma[i] = 0;
    for (int i = 0; i < _len; i++) {
        suma[i] += cifre[i] + number.cifre[i]; //number.GetDigit(i);
        if (suma[i] >= baza) {
            suma[i] -= baza;
            suma[i + 1] = 1;
        }
    }
    for (int i = 0; i < _len; i++) cifre[i] = suma[i];
}

int BigNumber::GetDigit(int i) {
    return cifre[i];
}

BigNumber BigNumber::operator + (BigNumber const &obj) {
    BigNumber suma;
    for (int i = 0; i < suma._len; i++) {
        suma.cifre[i] += cifre[i] + obj.cifre[i];
        if (suma.cifre[i] >= suma.baza) {
            suma.cifre[i] -= suma.baza;
            suma.cifre[i + 1] = 1;
        }
    }
    return suma;
}

bool BigNumber::operator < (BigNumber const &obj) {
    for (int i = _len - 1; i >= 0; i--) {
        if (obj.cifre[i] > cifre[i]) {
            return true;
        }
    }
    return false;
}

void BigNumber::PrintNumber() {
    int b = baza, size = 0;
    bool afisez = false;
    while(b > 1) {
        b /= 10;
        size++;
    }
    for (int i = _len - 1; i >= 0; i--) {
        if (afisez) {
            cout << setfill('0') << setw(size) << cifre[i];
        } else {
            if (cifre[i] != 0) {
                cout << cifre[i];
                afisez = true;
            }
        }
    }
    if (!afisez) cout << 0;
}

void BigNumber::PrintLineNumber() {
    PrintNumber();
    cout << endl;
}
