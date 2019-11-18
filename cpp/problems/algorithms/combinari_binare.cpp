// backtrancking recursiv
#include <iostream>
#include <fstream>
#include <ctime>
using namespace std;

void Bk(int col, int n, int &total, int a[20]) {
    if (col == n) {
        //for (int i = 0; i < n; i++) cout << a[i];
        //cout << endl;
        total++;
        return;
    }
    Bk(col + 1, n, total, a);
    if (a[col] == 0) a[col] = 1;
    else a[col] = 0;
    Bk(col + 1, n, total, a);
}

int main(int argc, char *argv[]) {
    clock_t start = clock();
    int n = 16, a[20], total = 0;
    for (int i = 0; i < n; i++) {
        a[i] = 0;
    }
    Bk(0, n, total, a);   
    clock_t end = clock();
    cout << "combinari total " << total << endl;
    cout << "ran in " << double(end - start) / CLOCKS_PER_SEC << "sec" << endl;
    return 0;
}
