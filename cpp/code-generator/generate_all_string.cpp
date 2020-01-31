#include <iostream>
using namespace std;

void BK(char code[10], int level) {
    if (level > 2) return;
    if (level == 2) {
        for (int i = 0; i < 2; i++) cout << code[i];
        cout << endl;
    }
    while (code[level] < 127) {
        code[level]++;
        BK(code, level + 1);
    }
    code[level] = 31;
}

int main(int argc, char *argv[]) {
    int n;
    char code[3];

    for (int i = 0; i < 3; i++) code[i] = 31;

    cout << "n = 3"; n = 3;
    BK(code, 0);
    return 0;
}
