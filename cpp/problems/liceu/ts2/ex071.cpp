// ts2 p42 e1 ver b
#include <iostream>
#include <fstream>
using namespace std;

int frecv[26], suma;

void numara(char ch) {
    if (ch >= 'A' && ch <= 'Z') {
        ++frecv[ch - 'A'];
        ++suma;
    }
}

void tipar() {
    for (char c = 'A'; c <= 'Z'; ++c) {
        cout << c << " " << frecv[c - 'A'] << " " << (float) frecv[c - 'A'] / suma * 100 << "\n";
    }
}

int main(int argc, char *argv[]) {
    fstream in("ex071.cpp");
    char ch;
    while(in >> ch) numara(ch);
    tipar();
    return 0;
}
