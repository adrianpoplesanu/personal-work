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
    for (int j = 0; j < m; j++) {
       int coloana = 0;
       for (int i = 0; i < n; i++) {
           coloana += (a[i] == 1) ? -d[i][j] : d[i][j];
       }
       if (coloana < 0) coloana = -coloana;
       suma += coloana;
    }
    if (total < suma) total = suma;
}

void back(int i) {
    if (i == n) {
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
