#include <iostream>
#include <fstream>
#include <ctime>
using namespace std;

int a[8];
ofstream out("test.txt");

char translate(int n) {
    switch (n) {
        case 1:
            return '0';
        break;
        case 2:
            return '1';
        break;
        case 3:
            return '2';
        break;
        case 4:
            return '3';
        break;
        case 5:
            return '4';
        break;
        case 6:
            return '5';
        break;
        case 7:
            return '6';
        break;
        case 8:
            return '7';
        break;
        case 9:
            return '8';
        break;
        case 10:
            return '9';
        break;
        case 11:
            return 'A';
        break;
        case 12:
            return 'B';
        break;
        case 13:
            return 'C';
        break;
        case 14:
            return 'D';
        break;
        case 15:
            return 'E';
        break;
        case 16:
            return 'F';
        break;
    }
    return 'X';
}

void back (int i) {
    if (i == 8) {
        for (int j = 0; j < 8; j++) cout << translate(a[j]);
        cout << "\n";
        //for (int j = 0; j < 8; j++) out << a[j] << " ";
        //out << "\n";
        //for (int j = 0; j < 8; j++) out << translate(a[i]);
        //out << '\n';
    } else {
        while (a[i] < 16) {
            a[i]++;
            back (i + 1);
        }
        a[i] = 0;
    }
}

int main (int argc, char *argv[]) {
    // A-F 0-9 : 6 litere + 10 cifre, 16 variante
    // this is the usual default password for TP-LINK routers
    float start = clock();
    for (int i = 0; i < 8; i++) a[i] = 0;
    back (0);
    out.close();
    cout << "ran for " << (clock() - start) / CLOCKS_PER_SEC << "\n";
    return 0;
}
