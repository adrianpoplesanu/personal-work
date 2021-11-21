#include <iostream>
#include <ctime>
using namespace std;

int n = 5;
int m = 3;
int a[16];
int total = 0;
int d[5][3] = {
    4, -2, 2,
    3, -1, 5,
    2, 0, -3,
    4, 1, -3,
    5, -3, 2
};

void afis() {
    int suma = 0;
    for (int i = 0; i < n; i++) {
       int linie = 0;
       for (int j = 0; j < m; j++) {
           linie += (a[j] == 1) ? -d[i][j] : d[i][j];
       }
       if (linie < 0) linie = -linie;
       suma += linie;
    }
    if (total < suma) total = suma;
}

void back(int i) {
    if (i == m) {
        afis();
    } else {
        for(int j = 0; j <= 1; j++) {
            a[i] = j;
            back(i + 1);
        }
    }
}

int main(int argc, char *argv[]) {
    double start = clock();
    back(0);
    cout << total << "\n";
    double end = (clock() - start) / CLOCKS_PER_SEC;
    cout << "ran for: " << end << " seconds\n";
    return 0;
}
