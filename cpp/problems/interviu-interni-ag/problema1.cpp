#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <time.h>

#define MAX_SIZE 10

using namespace std;

void init_mat(int **(&a)) {
    a = new int*[MAX_SIZE];
    for(int i = 0; i < MAX_SIZE; i++) {
        a[i] = new int[MAX_SIZE];
    }
}

void read_mat(int **a, int& n, int &m, ifstream &file_in) {
    // file_in trebuie pasat ca referinta pentru ca sufera modifica in interiorul functiei
    // modificarile trebuie sa fie vizibile si dupa terminarea apelului pentru ca se reflecta in starea pointerului catre fisier
    string line, number;
    n = 0;
    m = 0;
    while(file_in.good()) {
        getline(file_in, line);
        if (line.empty()) break;

        istringstream iss(line);
        m = 0;
        while(getline(iss, number, ' ')) {
            a[n][m] = stoi(number);
            m++;
        }
        n++;
    }
}

void print_mat(int **a, int n, int m, ofstream &file_out) {
    // file_out trebuie pasat ca referinta pentru ca sufera modifica in interiorul functiei
    // modificarile trebuie sa fie vizibile si dupa terminarea apelului pentru ca se reflecta in starea pointerului catre fisier
    for(int i = 0; i < n; i ++) {
        for(int j = 0; j < m; j++) {
            file_out<<a[i][j]<<" ";
        }
        file_out<<endl;
    }
    file_out<< n <<" x "<< m << endl;
}

int get_sorting_size(int n, int m) {
    return (n < m) ? n : m;
}

void swap_rows(int **a, int row1, int row2) {
    int *aux;
    aux = a[row1];
    a[row1] = a[row2];
    a[row2] = aux;
}

void swap_inline_items(int **a, int idx1, int idx2) {
    int aux;
    aux = a[idx1][idx1];
    a[idx1][idx1] = a[idx1][idx2];
    a[idx1][idx2] = aux;
    aux = a[idx2][idx1];
    a[idx2][idx1] = a[idx2][idx2];
    a[idx2][idx2] = aux;
}

void sort_mat(int **a, int n, int m) {
    int size = get_sorting_size(n, m);
    for (int i = 0; i < size - 1; i++) {
        for (int j = i + 1; j < size; j++) {
            if (a[i][i] > a[j][j]) {
                swap_rows(a, i, j);
                swap_inline_items(a, i, j);
            }
        }
    }
}

void sort_mat2(int **a, int n, int m) {
    int size = get_sorting_size(n, m);
    bool sortat = false;
    while(!sortat) {
        sortat = true;
        for (int i = 0; i < size - 1; i++) {
            if (a[i][i] > a[i + 1][i + 1]) {
                swap_rows(a, i, i + 1);
                swap_inline_items(a, i, i + 1);
                sortat = false;
            }
        }
    }
}

void sort_mat3(int **a, int n, int m) {
    
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cout<<"Usage: ./problema1 fisier.in fisier.out"<<endl;
        return -1;
    }

    clock_t start_time = clock();
    int n, m;
    int **a;

    ifstream file_in(argv[1]);
    ofstream file_out(argv[2]);

    init_mat(a);
    read_mat(a, n, m, file_in);
    sort_mat2(a, n, m);
    print_mat(a, n, m, file_out);

    file_in.close();
    file_out.close();

    cout<<"done... executed in "<<(double)(clock() - start_time)/CLOCKS_PER_SEC<<" secs"<<endl;
    return 0;
}
