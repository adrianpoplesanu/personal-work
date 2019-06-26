#include <iostream>
#include <fstream>
#include <time.h>

using namespace std;

void read_input(int tabla[10][10], int work[10][10], ifstream &in) {
    for(int i = 1; i <= 9; i++) {
        for (int j = 1; j <= 9; j++) {
            in>>tabla[i][j];
            work[i][j] = tabla[i][j];
        }
    }
}

void Init(int work[10][10], int i, int j) {
    work[i][j] = 0;
}

bool Am_Succesor(int work[10][10], int i, int j, int n) {
    if (work[i][j] < n) {
        work[i][j]++;
        return true;
    }
    return false;
}

bool verticalCheck(int work[10][10], int i, int j) {
    for (int k = 1; k <= 9; k++) {
        if ((k != j) && (work[i][k] == work[i][j])) return false;
    }
    return true;
}

bool horizontalCheck(int work[10][10], int i, int j) {
    for (int k = 1; k <= 9; k++) {
        if ((k != i) && (work[k][j] == work[i][j])) return false;
    }
    return true;
}

bool checkOneSum(int work[10][10], int i, int j, int x, int y) {
    int total = 0;
    for(int k = x + 1; k <= x + 3; k++) {
        for (int l = y + 1; l <= y + 3; l++)
            if (work[k][l] == work[i][j]) total++;
    }
    if (total > 1) return false;
    return true;
}

bool checkSmallSums(int work[10][10], int i, int j) {
    return
        checkOneSum(work, i, j, 0, 0) &&
        checkOneSum(work, i, j, 0, 3) &&
        checkOneSum(work, i, j, 0, 6) &&
        checkOneSum(work, i, j, 3, 0) &&
        checkOneSum(work, i, j, 3, 3) &&
        checkOneSum(work, i, j, 3, 6) &&
        checkOneSum(work, i, j, 6, 0) &&
        checkOneSum(work, i, j, 6, 3) &&
        checkOneSum(work, i, j, 6, 6);
}

bool E_Valid(int work[10][10], int tabla[10][10], int i, int j) {
    return verticalCheck(work, i, j) && horizontalCheck(work, i, j) && checkSmallSums(work, i, j);
}

bool Solutie(int work[10][10]) {
    int total = 0;
    for (int i = 1; i <= 9; i++)
        for (int j = 1; j <= 9; j++)
            if (work[i][j] == 0) total++;
    return total == 0;
}

void Tipar(int work[10][10], ofstream &out) {
    for (int i = 1; i <= 9; i++) {
        for (int j = 1; j <= 9; j++) {
            out<<work[i][j]<<" ";
        }
        out<<endl;
    }
}

void increment_indexes(int work[10][10], int &i, int &j, int tabla[10][10]) {
    j++;
    if (j > 9) {
        i++;
        j = 1;
    }
    if (tabla[i][j] == 0) Init(work, i, j); // asta doar daca nu e pe tabla
    if (tabla[i][j] != 0) increment_indexes(work, i, j, tabla);
}

void decrement_indexes(int work[10][10], int &i, int &j, int tabla[10][10]) {
    if (tabla[i][j] == 0) Init(work, i, j); // asta doar daca nu e pe tabla
    j--;
    if ((j == 0) && i > 1) { i--; j = 9; }
    if (i >= 1 && j >=1) {
        if (tabla[i][j] != 0) decrement_indexes(work, i, j, tabla);
    }
}

void back(int work[10][10], int tabla[10][10], ofstream &out) {
    int i, j;
    bool AS;
    i = 1; j = 0;
    increment_indexes(work, i, j, tabla); // this is so cool
    while ((i > 0) && (j > 0)) {
        do { } while ((AS = Am_Succesor(work, i, j, 9)) && !E_Valid(work, tabla, i, j));
        if (AS) {
            if (Solutie(work)) {
                Tipar(work, out);
                break;
            } else {
                increment_indexes(work, i, j, tabla);
                Init(work, i, j);
            }
        } else {
            decrement_indexes(work, i, j, tabla);
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        cout<<"Usage: ./sudoku sudoku.in sudoku.out"<<endl;
        return 1;
    }
    clock_t time_start = clock();

    ifstream in(argv[1]);
    ofstream out(argv[2]);

    int tabla[10][10];
    int work[10][10];

    read_input(tabla, work, in);
    back(work, tabla, out);

    in.close();
    out.close();

    cout<<"Execution took: "<<(double)(clock() - time_start)/CLOCKS_PER_SEC<<" seconds"<<endl;
    return 0;
}
