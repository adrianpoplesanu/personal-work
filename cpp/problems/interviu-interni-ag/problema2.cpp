#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <time.h>
#include <vector>

#define MAX_SIZE 10

using namespace std;

void init_mat(int **(&a)) {
    a = new int*[MAX_SIZE];
    for(int i = 0; i < MAX_SIZE; i++) {
        a[i] = new int[MAX_SIZE];
    }
}

void reset_visited(int **(&visited), int n, int m) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) visited[i][j] = 0;
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

void print_mat(int **a, int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout<<a[i][j]<<" ";
        }
        cout<<endl;
    }
}

void walk_island(int **a, int **(&visited), int& sum, int& num, int x, int y, int n, int m) {
    if (a[x][y] > 0 && !visited[x][y]) {
        sum += a[x][y];
        num++;
        visited[x][y] = 1;
        if (x + 1 < n) walk_island(a, visited, sum, num, x + 1, y, n, m);
        if (x - 1 >= 0) walk_island(a, visited, sum, num, x - 1, y, n, m);
        if (y + 1 < m) walk_island(a, visited, sum, num, x, y + 1, n, m);
        if (y - 1 >= 0) walk_island(a, visited, sum, num, x, y - 1, n, m);
    }
}

void parse_map(int **a, int **(&visited), int n, int m, int &total, vector<float> &means) {
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if (a[i][j] > 0 && !visited[i][j]) {
                int sum = 0, num = 0;
                walk_island(a, visited, sum, num, i, j, n, m);
                means.push_back((float)sum/num);
                total++;
            }
        }
    }
}


void print_result(ofstream &file_out, int total, vector<float> means) {
    file_out<<total<<endl;
    vector<float>::iterator it;
    for (it = means.begin(); it < means.end(); it++) file_out<<*it<<" ";
    file_out<<endl;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cout<<"Usage: ./problema1 fisier.in fisier.out"<<endl;
        return -1;
    }

    clock_t start_time = clock();
    int n, m;
    int **a;
    int **visited;
    int total = 0;
    vector<float> means;

    ifstream file_in(argv[1]);
    ofstream file_out(argv[2]);

    init_mat(a);
    init_mat(visited);
    read_mat(a, n, m, file_in);
    reset_visited(visited, n, m);
    parse_map(a, visited, n, m, total, means);
    print_result(file_out, total, means);

    file_in.close();
    file_out.close();

    cout<<"done... executed in "<<(double)(clock() - start_time)/CLOCKS_PER_SEC<<" secs"<<endl;
    return 0;
}
