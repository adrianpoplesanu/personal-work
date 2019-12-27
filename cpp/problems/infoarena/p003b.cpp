#include <iostream>
#include <fstream>
#include <ctime>
using namespace std;

void Bk(int i, int n, int m, int a[16][16], int col[16], int &total) {
    if (i == m) {
        int suma = 0;
        for (int j = 0; j < n; j++) {
            int suma_rand = 0;
            for(int k = 0; k < m; k++) suma_rand += a[j][k] * col[k];
            if (suma_rand < 0) suma_rand = -suma_rand;
            suma += suma_rand;
        }
        if (suma > total) total = suma;
        return;
    }
    Bk(i + 1, n, m, a, col, total);
    if (col[i] == -1) col[i] = 1;
    else col[i] = -1;
    Bk(i + 1, n, m, a, col, total);
}

int main(int argc, char *argv[]) {
    clock_t start = clock();
    ifstream in;
    ofstream out;
    in.open("in003.in");
    out.open("out003.out");

    int n, m, a[16][16], col[16], total = -2000000;
    in >> n >> m;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) in >> a[i][j];
    for (int i = 0; i < m; i++) col [i] = -1;
    Bk(0, n, m, a, col, total);
    out << total;

    in.close();
    out.close();
    clock_t end = clock();
    cout << "ran for " << double(end - start) / CLOCKS_PER_SEC << "secs" << endl;
    return 0;
}
